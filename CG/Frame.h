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

	~Frame() = default;

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

	void OnRenderingPoint(wxRibbonButtonBarEvent& e);

	void OnRenderingPointConfig(wxRibbonButtonBarEvent& e);

	void OnRenderingWireframe( wxRibbonButtonBarEvent& e);

	void OnRenderingWireframeConfig(wxRibbonButtonBarEvent& e);

	void OnRenderingVolume(wxRibbonButtonBarEvent& e);

	void OnRenderingVolumeConfig(wxRibbonButtonBarEvent& e);

	void OnRenderingSmooth(wxRibbonButtonBarEvent& e);

	void OnRenderingSmoothConfig(wxRibbonButtonBarEvent& e);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void OnParticleTranslate(wxRibbonButtonBarEvent& e);

	void OnParticleStroke(wxRibbonButtonBarEvent& e);

	void OnParticleErase(wxRibbonButtonBarEvent& e){};

	void OnCanvasConfig(wxRibbonButtonBarEvent& e);

	void OnCanvasClear(wxRibbonButtonBarEvent& e){};

	void OnVolumeConfig(wxRibbonButtonBarEvent& e);

	void OnWireFrameConfig(wxRibbonButtonBarEvent& e);

private:
	View* view;
	Model::MainModelSPtr model;

	void setRendering();

	void OnKeyDown(wxKeyEvent& event);

	void createPanels(wxRibbonPage* parent);

	void createFilePanel(wxRibbonPage* parent);

	void createCameraPanel(wxRibbonPage* parent);

	void createBrushPanel(wxRibbonPage* parent);

	void createCanvasPanel(wxRibbonPage* parent);

	void createRenderingPanel(wxRibbonPage* parent);

	void createHelpPanel(wxRibbonPage* parent);
	
	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif