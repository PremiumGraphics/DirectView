#ifndef __CRYSTAL_UI_FRAME_H__
#define __CRYSTAL_UI_FRAME_H__

#include "MainModel.h"

#include <memory>

namespace Crystal {
	namespace UI {
		class View;

class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

private:
	void OnNew( wxRibbonButtonBarEvent& );

	void OnClose( wxRibbonButtonBarEvent& );

	void OnFileOpen( wxRibbonButtonBarEvent& e );

	void OnFileSave( wxRibbonButtonBarEvent& );

	void OnFileSaveAs( wxRibbonButtonBarEvent& e );

	void OnImport( wxRibbonButtonBarEvent& e );

	void OnExport( wxRibbonButtonBarEvent& e);

	void OnCameraTranslate( wxRibbonButtonBarEvent& );

	void OnAbout( wxRibbonButtonBarEvent& );

	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnRendering( wxRibbonButtonBarEvent& e);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void OnParticleTranslate(wxRibbonButtonBarEvent& e);

	void OnParticleStroke(wxRibbonButtonBarEvent& e);

	void OnCreateVolume(wxRibbonButtonBarEvent& e);

	void OnVolumeConfig(wxRibbonButtonBarEvent& e);

	void OnWireFrameConfig(wxRibbonButtonBarEvent& e);

private:
	View* view;
	Model::MainModelSPtr<float> model;

	void setRendering();

	void OnKeyDown(wxKeyEvent& event);
	
	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif