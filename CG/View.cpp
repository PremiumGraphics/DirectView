#include <stdafx.h>
#include "View.h"

#include "../Math/Matrix3d.h"
#include "../Math/Quaternion.h"

#include "../Graphics/Polygon.h"

#include "Converter.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;


BEGIN_EVENT_TABLE( View, wxGLCanvas )
	EVT_MOUSE_EVENTS( View::OnMouse )
END_EVENT_TABLE()


View::View( Frame* parent, const int width, const int height  )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
frame( parent ),
mode( CAMERA_TRANSLATE ),
renderingMode( WIRE_FRAME )
{
	glContext.SetCurrent( *this );

//	const int attributes[] = {WX_GL_SAMPLE_BUFFERS};
//	bool b = IsDisplaySupported( attributes );

	Connect( wxEVT_PAINT, wxPaintEventHandler( View::OnPaint ) );
	Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( View::OnKeyDown ) );
	//Connect( wxEVT_MOUSE_EVENTS, wxMouseEventHandler( View::onMouse ) );
	Connect( wxEVT_SIZE, wxSizeEventHandler( View::OnSize ) );

	build();

	//texture = new TextureObject( pixels, 2, 1 );
}

View::~View()
{
	//delete texture;
}

#include "../Math/Vector3d.h"

using namespace Crystal::Math;


void View::OnPaint( wxPaintEvent& )
{
	wxPaintDC dc( this );

	const wxSize size = GetClientSize();

	glContext.SetCurrent(*this);

	glViewport(0, 0, size.x, size.y );

	draw( size );

	glFlush();

	SwapBuffers();
}

void View::OnKeyDown(wxKeyEvent& event)
{
	Camera<float>* camera = frame->getCamera();
	Vector3d pos = camera->getPos();

	switch ( event.GetKeyCode() ) {
	case WXK_RIGHT:
		pos += Vector3d( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_LEFT:
		pos -= Vector3d( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_DOWN:
		pos += Vector3d( 0.0f, 0.1f, 0.0f );
		break;
	case WXK_UP:
		pos -= Vector3d( 0.0f, 0.1f, 0.0f );
		break;
	default:
		event.Skip();
		return;
	};

	camera->setPos( pos );

	draw( GetSize() );

	SwapBuffers();

}

void View::OnMouse( wxMouseEvent& event )
{
	if (event.LeftDClick()) {
		if (mode == PICK_VERTEX) {
			const int width = GetClientSize().GetWidth();
			const int height = GetClientSize().GetHeight();
			std::vector< GLubyte > pixels(width * height * 4);
			glReadBuffer(GL_FRONT);
			glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels.front()));
			wxImage image(width, height);

			int index = 0;

			for (int y = height - 1; y >= 0; --y) {
				for (int x = 0; x < width; ++x) {
					image.SetRGB(x, y, pixels[index], pixels[index + 1], pixels[index + 2]);
					index += 4;
				}
			}

			const wxPoint& position = event.GetPosition();
			const unsigned char r = image.GetRed(position.x, position.y);
			const unsigned char g = image.GetGreen(position.x, position.y);
			const unsigned char b = image.GetBlue(position.x, position.y);
			wxMessageBox(wxString::Format("%d %d %d", r, g, b));
		}
	}

	if( event.Dragging() ) {
		Vector3d pos;
		Vector3d angle;

		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d( 0.0f, 0.0f, diff.y * 1.0f );
		}
		else if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			angle += Vector3d( diff.x * 0.01, diff.y * 0.01, 0.0f );
		}
		else if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d( diff.x * 0.1f, diff.y * 0.1f, 0.0f );	
		}
		
		if( mode == CAMERA_TRANSLATE ) {
			frame->getCamera()->move( pos );
			frame->getCamera()->addAngle( angle );
		}
		else if( mode == LIGHT_TRANSLATE ) {
			const std::list<Graphics::Light*> lights = frame->getLights();
			for (Light* l : lights) {
				Vector3d lpos = l->getPos();
				lpos += pos;
				l->setPos(lpos);
			}
		}
		else if( mode == POLYGON_SCALE ) {
			Graphics::PolygonGroupList& polygons = frame->getPolygons();
			const Vector3d scale = Vector3d(1.0, 1.0, 1.0) + pos.getScaled( 0.01f );// = pos.getScaled(0.99f);
			for( Graphics::PolygonGroup& p : polygons ) {
				p.getPolygon()->scale(scale);
			}
		}
		else if( mode == POLYGON_TRANSLATE ) {
			Graphics::PolygonGroupList& polygons = frame->getPolygons();
			for( Graphics::PolygonGroup& p : polygons ) {
				p.getPolygon()->move( pos );
				//p->rotate( matrix );
			}
		}
		else if( mode == POLYGON_ROTATE ) {
			Graphics::PolygonGroupList& polygons = frame->getPolygons();
			for (Graphics::PolygonGroup& p : polygons) {
				p.getPolygon()->rotateZ( pos.getX() );
			}
			/*
			Matrix3d matrix = Matrix3d::RotateX( angle.getX() ) * Matrix3d::RotateY( angle.getY() ) * Matrix3d::RotateZ( angle.getZ() );
			const PolygonList& polygons = frame->getModel()->getPolygonModel()->getSelectedPolygons();
			for( Graphics::Polygon* p : polygons ) {
				p->rotate( matrix );
			}
			*/
		}
		else if (mode == POLYGON_ROTATE_X) {
			Graphics::PolygonGroupList& polygons = frame->getPolygons();
			for (Graphics::PolygonGroup& p : polygons) {
				p.getPolygon()->rotateX(pos.getX());
			}
		}
		else if (mode == POLYGON_ROTATE_Y) {
			Graphics::PolygonGroupList& polygons = frame->getPolygons();
			for (Graphics::PolygonGroup& p : polygons) {
				p.getPolygon()->rotateY(pos.getX());
			}
		}
		else if (mode == POLYGON_ROTATE_Z) {
			Graphics::PolygonGroupList& polygons = frame->getPolygons();
			for (Graphics::PolygonGroup& p : polygons) {
				p.getPolygon()->rotateZ(pos.getX());
			}
		}
		else {
			assert( false );
		}

		draw( GetSize() );

		SwapBuffers();
    }

	mouseStart = event.GetPosition();
}

void View::OnSize(wxSizeEvent& e)
{
	draw( e.GetSize() );
}

void View::draw(const wxSize& size)
{
	const int width = size.GetWidth();
	const int height = size.GetHeight();

	buildDisplayList();
	
	if( renderingMode == RENDERING_MODE::WIRE_FRAME ) {
		wireFrameRenderer.render(width, height, *(frame->getCamera()), dispList);
	}
	else if( renderingMode == RENDERING_MODE::FLAT ) {
		//flatRenderer.render( width, height, frame->getModel() );
		//onScreenRenderer.render( width, height, flatRenderer.getTexture() );
	}
	else if (renderingMode == RENDERING_MODE::PHONG) {
		//Vector3dVector positions;
		//Vector3dVector normals;
		//std::vector< std::vector<unsigned int> > indices;
		//for (const PolygonGroup& g : frame->getPolygons()) {
		//	Graphics::Polygon* p = g.getPolygon();
		//	for (Graphics::Face* f : p->getFaces()) {
		//		const std::vector<unsigned int>& ids = f->getVertexIds();
		//		indices.push_back(ids);
		//		const Half
		//		const Vector3dVector& ps = f->getEdges(); ->getPositions();
		//		const Vector3dVector& ns = p->getNormals();

		//		positions.insert(positions.end(), ps.begin(), ps.end());
		//		normals.insert(normals.end(), ns.begin(), ns.end());

		//	}
		//}
		//SmoothRenderer::Param param;
		//param.positions = toArray(positions);
		//param.normals = toArray(normals);

		//Camera<float>* c = frame->getCamera();
		//param.eyePos = c->getPos().toArray();
		//param.projectionMatrix = c->getPerspectiveMatrix().toArray4x4();
		//param.modelviewMatrix = c->getModelviewMatrix().toArray4x4();

		//param.lights = frame->getLights();

		//for (Graphics::Material* m : frame->getMaterials() ) {
		//	param.matAmbient = m->getAmbient().toArray3();
		//	param.matDiffuse = m->getDiffuse().toArray3();
		//	param.matSpecular = m->getSpecular().toArray3();
		//	param.shininess = m->getShininess();
		//}

		///*
		//std::list< Material* > materials = frame->getMaterials();
		//for (Graphics::Polygon* p : frame->getPolygons()) {
		//	if (p->materialName.empty()) {
		//		continue;
		//	}
		//	Material* mat = nullptr;
		//	for (Graphics::Material* m : materials) {
		//		if (p->materialName == m->name) {
		//			mat = m;
		//		}
		//	}
		//}
		//*/
		//smoothRenderer.render(width, height, param, indices);
	}
	else if (renderingMode == RENDERING_MODE::NORMAL) {
		normalRenderer.render(width, height, *(frame->getCamera()), dispList );
	}
	else if (renderingMode == RENDERING_MODE::POINT) {
		pointRenderer.render(width, height, frame->getCamera(), dispList );
	}
	else if (renderingMode == RENDERING_MODE::ID) {
		idRenderer.render(width, height, *(frame->getCamera()), dispList );
	}
	else {
		assert( false );
	}
}

void View::build()
{
	wireFrameRenderer.build();
	smoothRenderer.build();
	normalRenderer.build();
	pointRenderer.build();
	idRenderer.build();
	/*
	wireFrameRenderer.build();
	flatRenderer.build();
	*/
}

void View::buildDisplayList()
{
	dispList.clear();
	const PolygonGroupList& groups = frame->getPolygons();
	for (const PolygonGroup& g : groups) {
		dispList.add(g.getPolygon());
	}
}