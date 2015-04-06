#ifndef __CRYSTAL_APP_VIEW_H__
#define __CRYSTAL_APP_VIEW_H__

#include "WireFrameRenderer.h"
#include "VectorRenderer.h"

#include "../CrystalShader/FastPointRenderer.h"

namespace Crystal {
	namespace App {
		class Frame;

class View : public wxGLCanvas
{
public:
	View( Frame *frame, int* args, const int width, const int height );

	~View();

	enum RenderingMode {
		WireFrame,
		Surface,
		VectorMap,
		PointSprite,
	};

	void setRenderingMode( const RenderingMode& m ) { this->renderingMode = m; }

	void setRenderingBlocks();

	float pointSize;

	float vectorScale;

	float lineWidth;

private:

	RenderingMode renderingMode;

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

	WireFrameRenderer meshRenderer;
	Graphics::VectorRenderer vectorRenderer;
	Graphics::FastPointRenderer pointRenderer;

	std::vector<float> positions;
	std::vector<float> cellCenters;

	std::vector<float> vertexValues;
	std::vector<float> cellValues;
	std::vector<float> vectors;
	std::vector<std::vector<unsigned int> > indices;
	float min;
	float max;
	bool isCell;
	std::vector< Graphics::ColorRGBA<float> > texColors;


	wxDECLARE_NO_COPY_CLASS( View );
};



	}
}

#endif