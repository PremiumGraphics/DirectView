#ifndef __CRYSTAL_UI_VIEW_H__
#define __CRYSTAL_UI_VIEW_H__

#include "View.h"

#include "Frame.h"

#include "../Shader/NormalRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Command/MainModel.h"

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

	float getPointSize() const { return model->getRenderingModel()->getConfig().pointSize; }

	float getLineWidth() const { return model->getRenderingModel()->getConfig().lineWidth; }

	float getNormalScale() const { return model->getRenderingModel()->getConfig().normalScale; }


	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif