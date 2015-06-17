#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../Shader/WireFrameRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/SmoothRenderer.h"
#include "../Shader/VolumeRenderer.h"

#include "../Command/Model.h"
#include "../Command/MainConfig.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace UI {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, const Command::ModelSPtr<float>& factory);

	~View();

	enum MODE{
		CAMERA_TRANSLATE,
		TRANSLATE,
		ROTATE,
		SCALE,
		//PICK_VERTEX,
	};

	enum class RENDERING_MODE {
		WIRE_FRAME,
		SURFACE,
		NORMAL,
		POINT,
		VOLUME,
		ID,
	};

	void setMode( const MODE& m ) { this->mode = m; }

	void setRenderingMode( const RENDERING_MODE& m ) { this->renderingMode = m; }

	void setConfig(const Command::RenderingConfig<float>& config) {
		this->config = config;
	}

	void set(const Command::Model<float>& model);

	//void set(const Command::VolumeModelSPtr<float>& model);


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
	const Command::ModelSPtr<float>& model;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	Shader::WireFrameRenderer wireFrameRenderer;
	Shader::SurfaceRenderer surfaceRenderer;
	//Graphics::SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	Shader::PointRenderer pointRenderer;
	Shader::IDRenderer idRenderer;
	Shader::VolumeRenderer vRenderer;

	Command::RenderingConfig<float> config;

	float getPointSize() const { return config.getPointConfig().getPointSize(); }

	float getLineWidth() const { return config.getWireframeConfig().getLineWidth(); }

	void set(const Command::SurfaceModelSPtr<float>& model);

	void set(const Command::VolumeModelSPtr<float>& model);

	void set(const Command::MetaballModelSPtr<float>& model);


	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif