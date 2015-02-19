#include <stdafx.h>
#include "View.h"

#include "../Math/Matrix3d.h"
#include "../Math/Quaternion.h"

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
mode( CameraTranslate ),
renderingMode( WireFrame )
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
		
		if( mode == CameraTranslate ) {
			frame->getCamera()->move( pos );
			frame->getCamera()->addAngle( angle );
		}
		else if( mode == LightTranslate ) {
			/*
			LightList& lights = frame->getModel()->getLightModel()->getSelectedLights();
			for( Light* l : lights ) {
				l->pos += pos;
			}
			*/
		}
		else if( mode == PolygonScale ) {
			/*
			const PolygonList& polygons = frame->getModel()->getPolygonModel()->getSelectedPolygons();
			pos.scale( 0.1f, 0.1f, 0.1f );
			pos += Vector3d( 1.0f, 1.0f, 1.0f );
			for( Graphics::Polygon* p : polygons ) {
				p->scale( pos.getX(), pos.getY(), pos.getZ() );
			}
			*/
		}
		else if( mode == PolygonTranslate ) {
			/*
			const PolygonList& polygons = frame->getModel()->getPolygonModel()->getSelectedPolygons();
			for( Graphics::Polygon* p : polygons ) {
				p->translate( pos );
				//p->rotate( matrix );
			}
			*/
		}
		else if( mode == PolygonRotate ) {
			/*
			Matrix3d matrix = Matrix3d::RotateX( angle.getX() ) * Matrix3d::RotateY( angle.getY() ) * Matrix3d::RotateZ( angle.getZ() );
			const PolygonList& polygons = frame->getModel()->getPolygonModel()->getSelectedPolygons();
			for( Graphics::Polygon* p : polygons ) {
				p->rotate( matrix );
			}
			*/
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
	
	if( renderingMode == RenderingMode::WireFrame ) {
		VectorVector positions;
		std::vector< std::vector<unsigned int> > indices;
		for (Graphics::Polygon* p : frame->getPolygons()) {
			const VectorVector& ps = p->positions;
			positions.insert(positions.end(), ps.begin(), ps.end());
			for (const Graphics::Face& f : p->faces) {
				const std::vector<unsigned int>& ids = f.vertexIds;
				indices.push_back(ids);
			}
		}
		WireFrameRenderer::Param param;
		param.positions = toArray(positions);/* {
			0.0, 0.0, 0.0,
			1.0, 0.0, 0.0,
			1.0, 1.0, 0.0
		}; */
		param.projectionMatrix = frame->getCamera()->getPerspectiveMatrix().toArray4x4();
		param.modelviewMatrix = frame->getCamera()->getModelviewMatrix().toArray4x4();

		wireFrameRenderer.render(width, height, param, indices);
	}
	else if( renderingMode == RenderingMode::Flat ) {
		//flatRenderer.render( width, height, frame->getModel() );
		//onScreenRenderer.render( width, height, flatRenderer.getTexture() );
	}
	else if (renderingMode == RenderingMode::Phong) {
		VectorVector positions;
		VectorVector normals;
		std::vector< std::vector<unsigned int> > indices;
		for (Graphics::Polygon* p : frame->getPolygons()) {
			const VectorVector& ps = p->positions;
			const VectorVector& ns = p->normals;
			positions.insert(positions.end(), ps.begin(), ps.end());
			normals.insert(normals.end(), ns.begin(), ns.end());
			for (const Graphics::Face& f : p->faces) {
				const std::vector<unsigned int>& ids = f.vertexIds;
				indices.push_back(ids);
			}
		}
		SmoothRenderer::Param param;
		param.positions = toArray(positions);
		param.normals = toArray(normals);

		Camera<float>* c = frame->getCamera();
		param.eyePos = c->getPos().toArray();
		param.projectionMatrix = c->getPerspectiveMatrix().toArray4x4();
		param.modelviewMatrix = c->getModelviewMatrix().toArray4x4();

		param.lights = *( frame->getLights() );

		for (Graphics::Material* m : frame->getMaterials() ) {
			param.matAmbient = m->getAmbient().toArray3();
			param.matDiffuse = m->getDiffuse().toArray3();
			param.matSpecular = m->getSpecular().toArray3();
			param.shininess = m->getShininess();
		}
		smoothRenderer.render(width, height, param, indices);
	}
	else {
		assert( false );
	}
}

void View::build()
{
	wireFrameRenderer.build();
	smoothRenderer.build();
	/*
	wireFrameRenderer.build();
	flatRenderer.build();
	*/
}
