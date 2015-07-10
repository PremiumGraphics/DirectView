#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "MainCommand.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace UI {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, Command::MainCommand& command);

	~View();

private:

	void OnPaint( wxPaintEvent& );

	void OnMouse( wxMouseEvent& e );

	void OnMouseWheel(wxMouseEvent& e);

	void OnLeftDoubleClick(wxMouseEvent& e);

	void OnRightDoubleClick(wxMouseEvent& e);

	void OnLeftDown(wxMouseEvent& e);

	void OnLeftUp(wxMouseEvent& e);

	void OnRightDown(wxMouseEvent& e);

	void OnRightUp(wxMouseEvent& e);

	void OnEnterWindow(wxMouseEvent& e);

	void OnMotion(wxMouseEvent& e);

	//void OnMouse

	void OnSize( wxSizeEvent& e );

	void draw(const wxSize& size);

private:
	Command::MainCommand& command;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	//Graphics::SmoothRenderer smoothRenderer;


	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif