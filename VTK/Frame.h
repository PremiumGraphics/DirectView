#ifndef __CRYSTAL_APP_FRAME_H__
#define __CRYSTAL_APP_FRAME_H__

#include <memory>

#include "View.h"
#include "../Graphics/Camera.h"
#include "../IO/VTKObject.h"
#include "../IO/VTKObjectFactory.h"

namespace Crystal {
	namespace App {
		class VTKTree;

class Frame : public wxFrame
{
public:
	Frame();

	~Frame();

public:
	//std::list<IO::VTKObject*> getVTKObject() { return factory.getObjects(); }
	IO::VTKObjectFactory* getFactory() { return &factory; }

	Graphics::Camera<float>* getCamera() { return &camera; }


private:

	void OnNew( wxRibbonButtonBarEvent& );

	void OnClose( wxRibbonButtonBarEvent& );

	void OnFileOpen( wxRibbonButtonBarEvent& e );

	void OnWireFrameRendering( wxRibbonButtonBarEvent& e );

	void OnVectorRendering( wxRibbonButtonBarEvent& e );

	void OnVectorRenderingDropDown( wxRibbonButtonBarEvent& e );

	void OnSurfaceRendering( wxRibbonButtonBarEvent& e );

	void OnPointRendering( wxRibbonButtonBarEvent& e );

	void OnPointRenderingDropDown( wxRibbonButtonBarEvent& e );

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void OnViewRefresh( wxRibbonToolBarEvent& e );

	void OnAbout( wxRibbonButtonBarEvent& e );

	void OnFileGenerate( wxRibbonToolBarEvent& e );
	
	//void OnSize( wxSizeEvent& e );

private:

	Graphics::Camera<float> camera;

	VTKTree* tree;

	View* view;

	int nextId;

	IO::VTKObjectFactory factory;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif