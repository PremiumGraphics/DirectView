#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "MainModel.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace UI {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, const Model::MainModelSPtr<float>& model);

	~View();


private:

	void OnPaint( wxPaintEvent& );

	void OnMouse( wxMouseEvent& e );

	//void OnMouse

	void OnSize( wxSizeEvent& e );

	void draw(const wxSize& size);

	DECLARE_EVENT_TABLE()

private:
	const Model::MainModelSPtr<float>& model;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	//Graphics::SmoothRenderer smoothRenderer;


	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif