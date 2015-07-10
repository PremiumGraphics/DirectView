#include <stdafx.h>
#include "View.h"

#include "../Graphics/Surface.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;
using namespace Crystal::UI;


View::View( Frame* parent, const int width, const int height, MainCommand& model )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE | wxWANTS_CHARS ),
glContext( this ),// width, height ),
command( model )
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

	Connect(wxEVT_MOTION,		wxMouseEventHandler(View::OnMotion));

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
	command.onLeftDoubleClick();
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
	command.onRightDoubleClick();
	draw(GetSize());
	SwapBuffers();
}

void View::OnLeftDown(wxMouseEvent& e)
{
	command.onLeftButtonDown();
	draw(GetSize());
	SwapBuffers();
}

void View::OnLeftUp(wxMouseEvent& e)
{
	command.onLeftButtonUp();
	draw(GetSize());
	SwapBuffers();
}

void View::OnRightDown(wxMouseEvent& e)
{
	command.onRightButtonDown();
	draw(GetSize());
	SwapBuffers();
}

void View::OnRightUp(wxMouseEvent& e)
{
	command.onRightButtonUp();
	draw(GetSize());
	SwapBuffers();
}

void View::OnEnterWindow(wxMouseEvent& e)
{
	SetFocus();
}

void View::OnMotion(wxMouseEvent& event)
{
	if (event.Moving()) {
		wxPoint position = event.GetPosition();
		const wxPoint diff = position - mouseStart;
		Vector3d<float> middle(diff.x * 0.01, diff.y * 0.01, 0.0f);

		command.onMoving(middle);
		draw(GetSize());
		SwapBuffers();

		mouseStart = event.GetPosition();

	}

	//wxPoint mouseStart(model.getMousePosition().x, model.getMousePosition().y);


	if (event.Dragging()) {
		if (event.MiddleIsDown()) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			Vector3d<float> middle(diff.x * 0.01, diff.y * 0.01, 0.0f);
			command.onDraggindMiddle(middle);
		}
		if (event.RightIsDown()) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			Vector3d<float> right = Vector3d<float>(diff.x * 0.01, diff.y * 0.01, 0.0f);
			command.onDraggingRight(right);
		}
		if (event.LeftIsDown()) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			Vector3d<float> left = Vector3d<float>(diff.x * 0.01f, diff.y * 0.01, 0.0f);
			command.onDraggingLeft(left);
		}

		draw(GetSize());

		SwapBuffers();
	}


	//wxPoint mouseEnd = event.GetPosition();
	mouseStart = event.GetPosition();

}

void View::OnMouseWheel(wxMouseEvent& e)
{
	const auto dt = e.GetWheelDelta() / 1200.0f;
	if (e.GetWheelRotation() > 0) {
		command.onMouseWheel(dt);
	}
	else {
		command.onMouseWheel(-dt);
	}
	draw(GetSize());
	SwapBuffers();
}


void View::OnSize(wxSizeEvent& e)
{
	draw( e.GetSize() );
}



void View::draw(const wxSize& size)
{
	const int width = size.GetWidth();
	const int height = size.GetHeight();

	command.render(width, height);
}
