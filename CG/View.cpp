#include <stdafx.h>
#include "View.h"

#include "../Graphics/Surface.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;
using namespace Crystal::UI;


BEGIN_EVENT_TABLE( View, wxGLCanvas )
	EVT_MOUSE_EVENTS( View::OnMouse )
END_EVENT_TABLE()


View::View( Frame* parent, const int width, const int height, MainCommand& model )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE | wxWANTS_CHARS ),
glContext( this ),// width, height ),
model( model )
{
	glContext.SetCurrent( *this );

//	const int attributes[] = {WX_GL_SAMPLE_BUFFERS};
//	bool b = IsDisplaySupported( attributes );

	Connect(wxEVT_PAINT, wxPaintEventHandler(View::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(View::OnSize));


	Connect(wxEVT_LEFT_DCLICK,	wxMouseEventHandler(View::OnLeftDoubleClick));
	Connect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(View::OnRightDoubleClick));

	Connect(wxEVT_LEFT_DOWN,	wxMouseEventHandler(View::OnLeftDown));
	Connect(wxEVT_LEFT_UP,		wxMouseEventHandler(View::OnLeftUp));

	Connect(wxEVT_RIGHT_DOWN,	wxMouseEventHandler(View::OnRightDown));
	Connect(wxEVT_RIGHT_UP,		wxMouseEventHandler(View::OnRightUp));

	Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(View::OnEnterWindow));
	Connect(wxEVT_MOUSEWHEEL,	wxMouseEventHandler(View::OnMouseWheel));

	model.buildRenderer();
}

View::~View()
{
}



void View::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);

	const wxSize size = GetClientSize();

	glContext.SetCurrent(*this);

	glViewport(0, 0, size.x, size.y);

	draw(size);

	glFlush();

	SwapBuffers();
}

void View::OnLeftDoubleClick(wxMouseEvent& e)
{
	model.onLeftDoubleClick();
	draw(GetSize());
	SwapBuffers();
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
	//model->setRendering();
	//Refresh();
	//model->bakeParticleToVolume();
}

void View::OnRightDoubleClick(wxMouseEvent& e)
{
	model.onRightDoubleClick();
	draw(GetSize());
	SwapBuffers();
}

void View::OnLeftDown(wxMouseEvent& e)
{
	model.onLeftButtonDown();
	draw(GetSize());
	SwapBuffers();
}

void View::OnLeftUp(wxMouseEvent& e)
{
	model.onLeftButtonUp();
	draw(GetSize());
	SwapBuffers();
}

void View::OnRightDown(wxMouseEvent& e)
{
	model.onRightButtonDown();
	draw(GetSize());
	SwapBuffers();
}

void View::OnRightUp(wxMouseEvent& e)
{
	model.onRightButtonUp();
	draw(GetSize());
	SwapBuffers();
}

void View::OnEnterWindow(wxMouseEvent& e)
{
	SetFocus();
}

void View::OnMouse(wxMouseEvent& event)
{
	if (event.Moving()) {
		wxPoint position = event.GetPosition();
		const wxPoint diff = position - mouseStart;
		Vector3d<float> middle(diff.x * 0.01, diff.y * 0.01, 0.0f);

		model.onMoving(middle);
		draw(GetSize());
		SwapBuffers();

		mouseStart = event.GetPosition();

	}

	//wxPoint mouseStart(model.getMousePosition().x, model.getMousePosition().y);


	if( event.Dragging() ) {
		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			Vector3d<float> middle(diff.x * 0.01, diff.y * 0.01, 0.0f);
			model.onDraggindMiddle(middle);
		}
		if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			Vector3d<float> right = Vector3d<float>( diff.x * 0.01, diff.y * 0.01, 0.0f );
			model.onDraggingRight(right);
		}
		if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			Vector3d<float> left = Vector3d<float>( diff.x * 0.01f, diff.y * 0.01, 0.0f );	
			model.onDraggingLeft(left);
		}
		
		draw( GetSize() );

		SwapBuffers();
    }


	//wxPoint mouseEnd = event.GetPosition();
	mouseStart = event.GetPosition();
}

void View::OnMouseWheel(wxMouseEvent& e)
{
	const auto dt = e.GetWheelDelta() / 1200.0f;
	if (e.GetWheelRotation() > 0) {
		model.onMouseWheel(dt);
	}
	else {
		model.onMouseWheel(-dt);
	}
	draw(GetSize());
	SwapBuffers();

	//e.GetWheelDelta() 
	/*if (e.MiddleIsDown()) {

	}*/
}


void View::OnSize(wxSizeEvent& e)
{
	draw( e.GetSize() );
}



void View::draw(const wxSize& size)
{
	const int width = size.GetWidth();
	const int height = size.GetHeight();

	model.render(width, height);
}
