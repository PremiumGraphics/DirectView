#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../CrystalShader/WireFrameRenderer.h"
#include "../CrystalShader/NormalRenderer.h"
#include "../CrystalShader/IDRenderer.h"
#include "../CrystalShader/PointRenderer.h"
#include "../CrystalShader/SmoothRenderer.h"


#include "../Graphics/DisplayList.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace CG {

class View : public wxGLCanvas
{
public:
	View( Frame *frame, const int width, const int height, Model& model );

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
		//PICK_VERTEX,
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

	float getPointSize() const { pointSize; }

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
	Model& model;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	Graphics::WireFrameRenderer wireFrameRenderer;
	Graphics::SurfaceRenderer surfaceRenderer;
	Graphics::SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	Graphics::PointRenderer pointRenderer;
	Graphics::IDRenderer idRenderer;

	Graphics::DisplayList dispList;
	Graphics::DisplayList dispListSelected;

	float pointSize;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif