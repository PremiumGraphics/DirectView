#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "WireFrameRenderer.h"
#include "SmoothRenderer.h"
#include "NormalRenderer.h"
#include "PointRenderer.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace CG {

class View : public wxGLCanvas
{
public:
	View( Frame *frame, const int width, const int height );

	~View();

	enum Mode{
		PolygonTranslate,
		PolygonScale,
		PolygonRotate,
		CameraTranslate,
		LightTranslate,
	};

	enum RenderingMode {
		WireFrame,
		Phong,
		Flat,
		Normal,
		Point,
	};

	void setMode( const Mode& m ) { this->mode = m; }

	void setRenderingMode( const RenderingMode& m ) { this->renderingMode = m; }

private:
	Mode mode;

	RenderingMode renderingMode;

	void OnPaint( wxPaintEvent& );

	void OnKeyDown( wxKeyEvent& e );

	void OnMouse( wxMouseEvent& e );

	void OnSize( wxSizeEvent& e );

	void draw(const wxSize& size);

	DECLARE_EVENT_TABLE()

private:
	wxGLContext glContext;

	Frame* frame;

	wxPoint mouseStart;
	
	void build();

	WireFrameRenderer wireFrameRenderer;
	SmoothRenderer smoothRenderer;
	NormalRenderer normalRenderer;
	PointRenderer pointRenderer;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif