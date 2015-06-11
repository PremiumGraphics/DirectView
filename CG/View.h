#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../Shader/WireFrameRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Command/RenderingCommand.h"

#include "../Command/ScalarSpaceTransformCommand.h"

#include "../Command/MainFactory.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace UI {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, const Command::MainFactory& factory, const Command::ScalarSpaceTransformCommandSPtr<float>& ssTransformCmd);

	~View();

	enum MODE{
		CAMERA_TRANSLATE,
		LIGHT_TRANSLATE,
		SPACE_TRANSFORM,
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

	float getPointSize() const { pCommand.getPointSize(); }

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
	const Command::MainFactory& factory;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	Shader::WireFrameRenderer wireFrameRenderer;
	Shader::SurfaceRenderer surfaceRenderer;
	//Graphics::SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	Shader::PointRenderer pointRenderer;
	Shader::IDRenderer idRenderer;

	Command::WireFrameRenderingCommand<float,float> wCommand;
	Command::PointRenderingCommand<float> pCommand;
	Command::NormalRenderingCommand<float> nCommand;

	Command::ScalarSpaceTransformCommandSPtr<float> ssTransformCmd;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif