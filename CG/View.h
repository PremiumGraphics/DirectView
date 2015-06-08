#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../Shader/WireFrameRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "RenderingCommand.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace CGS {

class View : public wxGLCanvas
{
public:
	View( Frame *frame, const int width, const int height, Command::Model& model );

	~View();

	enum MODE{
		CAMERA_TRANSLATE,
		LIGHT_TRANSLATE,
		//PICK_VERTEX,
	};

	enum RENDERING_MODE {
		WIRE_FRAME,
		FLAT,
		NORMAL,
		POINT,
		ID,
	};

	void setMode( const MODE& m ) { this->mode = m; }

	void setRenderingMode( const RENDERING_MODE& m ) { this->renderingMode = m; }

	float getPointSize() const { rCommand.getPointSize(); }

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
	Command::Model& model;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	Shader::WireFrameRenderer wireFrameRenderer;
	Shader::SurfaceRenderer surfaceRenderer;
	//Graphics::SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	Shader::PointRenderer pointRenderer;
	Shader::IDRenderer idRenderer;

	RenderingCommand rCommand;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif