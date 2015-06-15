#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../Shader/WireFrameRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Command/RenderingBuffer.h"

#include "../Command/MainFactory.h"
#include "../Command/MainConfig.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace UI {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, const Command::MainFactory<float>& factory, const Command::RenderingBufferSPtr<float>& rCommand);

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

	void setConfig(const Command::RenderingConfig<float>& config) {
		this->config = config;
	}

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
	const Command::MainFactory<float>& factory;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	Shader::WireFrameRenderer wireFrameRenderer;
	Shader::SurfaceRenderer surfaceRenderer;
	//Graphics::SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	Shader::PointRenderer pointRenderer;
	Shader::IDRenderer idRenderer;

	Command::RenderingConfig<float> config;

	float getPointSize() const { return config.getPointConfig().getPointSize(); }

	float getLineWidth() const { return config.getWireframeConfig().getLineWidth(); }


	Command::RenderingBufferSPtr<float> rCommand;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif