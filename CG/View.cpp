#include <stdafx.h>
#include "View.h"

#include "../Graphics/Surface.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;


BEGIN_EVENT_TABLE( View, wxGLCanvas )
	EVT_MOUSE_EVENTS( View::OnMouse )
END_EVENT_TABLE()


View::View( Frame* parent, const int width, const int height, const MainModelSPtr<float>& model )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
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
}

View::~View()
{
}



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
	CameraSPtr<float> camera = model->getCamera();
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
		wxMessageBox(wxString::Format("%d %d %d", r, g, b));

		const Object::Type& type = static_cast<Object::Type>(r);
		const unsigned int id = g;
		model->changeSelected(type, id);
		model->setRendering();
		Refresh();

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
		
		if( model->getUIMode() == CAMERA_TRANSLATE ) {
			model->getCamera()->move( pos );
			model->getCamera()->addAngle( angle );
		}
		else if (model->getUIMode() == TRANSLATE) {
			model->move(pos);
			model->polygonize();
			model->setRendering();
			//ssTransformCmd->move(pos);
		}
		else if (model->getUIMode() == ROTATE) {
			model->rotate(angle);
			model->setRendering();
		}
		else if (model->getUIMode() == SCALE) {
			model->scale(Vector3d<float>(1,1,1) + pos*0.01f);
			model->setRendering();
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

	Camera<float> c = *(model->getCamera());

	glPointSize(getPointSize());

	if( model->getRenderingModel()->getMode() == Model::RenderingModel<float>::Mode::WIRE_FRAME ) {
		glLineWidth( getLineWidth() );
		wireframeRenderer.render(width, height, c, model->getRenderingModel()->getLineBuffer() );

		glPointSize( this->getPointSize() );
		wireframeRenderer.render(width, height, c, model->getRenderingModel()->getPointBuffer());
	}
	else if (model->getRenderingModel()->getMode() == Model::RenderingModel<float>::Mode::SURFACE) {
		wireframeRenderer.render(width, height, c, model->getRenderingModel()->getTriangleBuffer());
		//surfaceRenderer.render(width, height, c );
	}
	else {
		assert( false );
	}
}

void View::build()
{
	normalRenderer.build();
	wireframeRenderer.build();
}