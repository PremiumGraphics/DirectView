#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../Shader/NormalRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Command/MainModel.h"
#include "../Command/MainConfig.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace UI {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, const Model::MainModelSPtr<float>& factory);

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
	};

	void setMode( const MODE& m ) { this->mode = m; }

	void setRenderingMode( const RENDERING_MODE& m ) { this->renderingMode = m; }

	void setConfig(const Model::RenderingConfig<float>& config) {
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
	const Model::MainModelSPtr<float>& model;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	//Graphics::SmoothRenderer smoothRenderer;
	Graphics::NormalRenderer normalRenderer;
	Shader::WireframeRenderer wireframeRenderer;

	Model::RenderingConfig<float> config;

	float getPointSize() const { return config.pointSize; }

	float getLineWidth() const { return config.lineWidth; }

	float getNormalScale() const { return config.normalScale; }


	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif