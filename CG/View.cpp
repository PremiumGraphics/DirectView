#include <stdafx.h>
#include "View.h"

#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"

#include "../Graphics/Polygon.h"

#include "Converter.h"

using namespace Crystal::Graphics;
using namespace Crystal::Command;
using namespace Crystal::UI;


BEGIN_EVENT_TABLE( View, wxGLCanvas )
	EVT_MOUSE_EVENTS( View::OnMouse )
END_EVENT_TABLE()


View::View( Frame* parent, const int width, const int height, const MainFactory& factory, const RenderingBufferSPtr<float>& rCommand )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
mode( CAMERA_TRANSLATE ),
renderingMode( WIRE_FRAME ),
factory( factory ),
rCommand( rCommand )
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

#include "../Math/Vector.h"

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
	CameraSPtr<float> camera = factory.getCamera();
	Vector3d<float> pos = camera->getPos();

	switch ( event.GetKeyCode() ) {
	case WXK_RIGHT:
		pos += Vector3d<float>( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_LEFT:
		pos -= Vector3d<float>( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_DOWN:
		pos += Vector3d<float>( 0.0f, 0.1f, 0.0f );
		break;
	case WXK_UP:
		pos -= Vector3d<float>( 0.0f, 0.1f, 0.0f );
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

		//ssTransformCmd->add()
		//const Math::ScalarSpace3dSPtr<float>& selected = factory.getScalarSpaceFactory()->getScalarSpaces(r);
		/*
		if (selected != nullptr) {
			ssTransformCmd->add(selected);
		}
		*/
		//frame->selectedFace = frame->get
		return;
	}

	if( event.Dragging() ) {
		Vector3d<float> pos;
		Vector3d<float> angle;

		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d<float>( 0.0f, 0.0f, diff.y * 1.0f );
		}
		else if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			angle += Vector3d<float>( diff.x * 0.01, diff.y * 0.01, 0.0f );
		}
		else if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d<float>( diff.x * 0.1f, diff.y * 0.1f, 0.0f );	
		}
		
		if( mode == CAMERA_TRANSLATE ) {
			factory.getCamera()->move( pos );
			factory.getCamera()->addAngle( angle );
		}
		else if( mode == LIGHT_TRANSLATE ) {
			const LightSPtrList& lights = factory.getLightFactory()->getLights();
			for (const LightSPtr& l : lights) {
				Vector3d<float> lpos = l->getPos();
				lpos += pos;
				l->setPos(lpos);
			}
		}
		else if (mode == SPACE_TRANSFORM) {
			//ssTransformCmd->move(pos);
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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Camera<float> c = *(factory.getCamera());

	if( renderingMode == RENDERING_MODE::WIRE_FRAME ) {
		glLineWidth(1.0f);
		wireFrameRenderer.positions = rCommand->getWireframeCommand()->getPositions();
		wireFrameRenderer.colors = rCommand->getWireframeCommand()->getColors();
		wireFrameRenderer.render(width, height, c );
	}
	else if( renderingMode == RENDERING_MODE::FLAT ) {
		surfaceRenderer.render(width, height, c );
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	else if (renderingMode == RENDERING_MODE::NORMAL) {
		normalRenderer.positions = rCommand->getNormalRenderingCommand()->getPositions();
		normalRenderer.normals = rCommand->getNormalRenderingCommand()->getNormals();
		normalRenderer.render(width, height, c );
	}
	else if (renderingMode == RENDERING_MODE::POINT) {
		pointRenderer.positions = rCommand->getPointRenderingCommand()->getPoints();
		glPointSize( getPointSize());
		pointRenderer.render(width, height, &c );
	}
	else if (renderingMode == RENDERING_MODE::ID) {
		idRenderer.positions = rCommand->getPointRenderingCommand()->getPoints();
		idRenderer.ids = rCommand->getPointRenderingCommand()->getIds();
		glPointSize( getPointSize());
		idRenderer.render(width, height, c );
	}
	else {
		assert( false );
	}
}

void View::build()
{
	wireFrameRenderer.build();
	//smoothRenderer.build();
	normalRenderer.build();
	pointRenderer.build();
	idRenderer.build();
	surfaceRenderer.build();
	/*
	wireFrameRenderer.build();
	flatRenderer.build();
	*/
}