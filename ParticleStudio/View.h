#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "View.h"

#include "Frame.h"

//#include "../Shader/PointRenderer.h"
#include "ParticleRenderer.h"

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

	void buildDisplayList();

	float getPointSize() const { pointSize; }

private:
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

	std::vector<float> positions;
	std::vector<unsigned int> ids;

	//Shader::PointRenderer pointRenderer;
	Shader::ParticleRenderer pointRenderer;

	float pointSize;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif