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


View::View( Frame* parent, const int width, const int height, Model& model  )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
mode( CAMERA_TRANSLATE ),
renderingMode( WIRE_FRAME ),
pointSize( 10.0f ),
model( model )
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
	Camera<float>* camera = model.getCamera();
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
		wxMessageBox(wxString::Format("%d %d %d vertex id = %d face id = %d polygon id = %d", r, g, b, r, g, b));
		model.setSelectedVertex( r );
		model.setSelectedFace( g );
		//frame->selectedFace = frame->get
		return;
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
			model.getCamera()->move( pos );
			model.getCamera()->addAngle( angle );
		}
		else if( mode == LIGHT_TRANSLATE ) {
			const LightSPtrList& lights = model.getLights();
			for (const LightSPtr& l : lights) {
				Vector3d lpos = l->getPos();
				lpos += pos;
				l->setPos(lpos);
			}
		}
		else if( mode == POLYGON_SCALE ) {
			Graphics::PolygonSPtrList& polygons = model.getPolygons();
			const Vector3d scale = Vector3d(1.0, 1.0, 1.0) + pos.getScaled( 0.01f );// = pos.getScaled(0.99f);
			for( const PolygonSPtr& p : polygons ) {
				p->scale(scale);
			}
		}
		else if( mode == POLYGON_TRANSLATE ) {
			Graphics::PolygonSPtrList& polygons = model.getPolygons();
			for( const PolygonSPtr& p : polygons ) {
				p->move( pos );
				//p->rotate( matrix );
			}
		}
		else if( mode == POLYGON_ROTATE ) {
			Graphics::PolygonSPtrList& polygons = model.getPolygons();
			for( const PolygonSPtr& p : polygons) {
				p->rotateZ( pos.getX() );
			}
		}
		else if (mode == POLYGON_ROTATE_X) {
			PolygonSPtrList& polygons = model.getPolygons();
			for ( const PolygonSPtr& p : polygons) {
				p->rotateX(pos.getX());
			}
		}
		else if (mode == POLYGON_ROTATE_Y) {
			PolygonSPtrList& polygons = model.getPolygons();
			for (const PolygonSPtr& p : polygons) {
				p->rotateY(pos.getX());
			}
		}
		else if (mode == POLYGON_ROTATE_Z) {
			PolygonSPtrList& polygons = model.getPolygons();
			for (const PolygonSPtr& p : polygons) {
				p->rotateZ(pos.getX());
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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Camera<float> c = *(model.getCamera());

	if( renderingMode == RENDERING_MODE::WIRE_FRAME ) {
		glLineWidth(1.0f);
		wireFrameRenderer.render(width, height, c, dispList);
		glClear(GL_DEPTH_BUFFER_BIT);
		glLineWidth(5.0f);
		wireFrameRenderer.render(width, height, c, dispListSelected);
	}
	else if( renderingMode == RENDERING_MODE::FLAT ) {
		surfaceRenderer.render(width, height, c, dispList);
		glClear(GL_DEPTH_BUFFER_BIT);
		surfaceRenderer.render(width, height, c, dispListSelected);
	}
	else if (renderingMode == RENDERING_MODE::PHONG) {
		smoothRenderer.render(width, height, c, dispList, model.getLights(), model.getMaterials() );
	}
	else if (renderingMode == RENDERING_MODE::NORMAL) {
		normalRenderer.render(width, height, c, dispList );
	}
	else if (renderingMode == RENDERING_MODE::POINT) {
		glPointSize(pointSize);
		pointRenderer.render(width, height, &c, dispList );
	}
	else if (renderingMode == RENDERING_MODE::ID) {
		idRenderer.render(width, height, c, dispList );
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
	surfaceRenderer.build();
	/*
	wireFrameRenderer.build();
	flatRenderer.build();
	*/
}

void View::buildDisplayList()
{
	dispList.clear();
	dispListSelected.clear();
	const PolygonSPtrList& polygons = model.getPolygons();
	for (const PolygonSPtr& p : polygons) {
		dispList.add( p );
	}
	const FaceSPtrVector& faces = model.getSelectedFaces();
	for (const FaceSPtr& f : faces) {
		dispListSelected.add(f.get(), ColorRGBA<float>::Blue());
	}
}