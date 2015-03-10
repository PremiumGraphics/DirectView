#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "SmoothRenderer.h"
#include "PointRenderer.h"
#include "IDRenderer.h"

#include "../Graphics/WireFrameRenderer.h"
#include "../Graphics/NormalRenderer.h"


#include "../Graphics/DisplayList.h"

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

	enum MODE{
		POLYGON_TRANSLATE,
		POLYGON_SCALE,
		POLYGON_ROTATE,
		POLYGON_ROTATE_X,
		POLYGON_ROTATE_Y,
		POLYGON_ROTATE_Z,

		CAMERA_TRANSLATE,
		LIGHT_TRANSLATE,
		PICK_VERTEX,
	};

	enum RENDERING_MODE {
		WIRE_FRAME,
		PHONG,
		FLAT,
		NORMAL,
		POINT,
		ID,
	};

	void buildDisplayList();

	void setMode( const MODE& m ) { this->mode = m; }

	void setRenderingMode( const RENDERING_MODE& m ) { this->renderingMode = m; }

	float getPointSize() const { pointRenderer.getPointSize(); }

private:
	MODE mode;

	RENDERING_MODE renderingMode;

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

	Graphics::WireFrameRenderer wireFrameRenderer;
	SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	PointRenderer pointRenderer;
	IDRenderer idRenderer;

	Graphics::DisplayList dispList;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif