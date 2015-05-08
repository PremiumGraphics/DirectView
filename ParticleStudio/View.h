#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "View.h"

#include "Frame.h"

//#include "../Shader/PointRenderer.h"
#include "../Shader/ParticleRenderer.h"
#include "../Graphics/ParticleDisplayList.h"

namespace Crystal {
	namespace Graphics {
		class Color;
	}
	namespace CG {

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height, IO::Model& model);

	~View();

	void buildDisplayList();

	float getPointSize() const { return pointSize; }

	void setPointSize(const int size) { this->pointSize = size; }

private:
	void OnPaint( wxPaintEvent& );

	void OnKeyDown( wxKeyEvent& e );

	void OnMouse( wxMouseEvent& e );

	void OnSize( wxSizeEvent& e );

	void draw(const wxSize& size);

	DECLARE_EVENT_TABLE()

private:
	IO::Model& model;
	wxGLContext glContext;

	wxPoint mouseStart;
	
	void build();

	//Shader::PointRenderer pointRenderer;
	Shader::ParticleRenderer pointRenderer;
	Graphics::ParticleDisplayList list;
	Graphics::ParticleDisplayList selectedList;


	float pointSize;

	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif