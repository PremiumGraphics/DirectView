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

	model->buildRenderer();
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
		/*
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
		//wxMessageBox(wxString::Format("%d %d %d", r, g, b));

		const unsigned int id = g;
		*/
		model->bakeParticleToVolume();
		//model->setRendering();
		Refresh();

		return;
	}

	if( event.Dragging() ) {
		Vector3d<float> right;
		Vector3d<float> middle;
		Vector3d<float> left;

		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			middle += Vector3d<float>( diff.x * 0.01, 0.0f, 0.0f );
		}
		else if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			right += Vector3d<float>( diff.x * 0.01, diff.y * 0.01, 0.0f );
		}
		else if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			left += Vector3d<float>( diff.x * 0.01f, -(diff.y * 0.01f), 0.0f );	
		}
		
		model->move(left, middle, right);

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

	model->render(width, height);
}
