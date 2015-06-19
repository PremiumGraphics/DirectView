#ifndef __CRYSTAL_UI_FRAME_H__
#define __CRYSTAL_UI_FRAME_H__

#include "../Command/MainModel.h"
#include "../Command/MainConfig.h"

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

	void OnCreateLight( wxRibbonButtonBarEvent& );

	//void OnPick(wxRibbonButtonBarEvent&);

	void OnAbout( wxRibbonButtonBarEvent& );

	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnRenderWireFrame( wxRibbonButtonBarEvent& e);

	void OnPhong( wxRibbonButtonBarEvent& );

	void OnRenderSurface( wxRibbonButtonBarEvent& );

	void OnRenderNormal(wxRibbonButtonBarEvent&);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void OnCreateMetaball(wxRibbonButtonBarEvent& e);


	void OnCreateVolume(wxRibbonButtonBarEvent& e);


	void OnBooleanUnion(wxRibbonButtonBarEvent& e);

	void OnBooleanDiff(wxRibbonButtonBarEvent& e);

	void OnBooleanIntersection(wxRibbonButtonBarEvent& e);

	void OnBooleanNot(wxRibbonButtonBarEvent& e);

	void OnTranslate(wxRibbonButtonBarEvent& e);

	void OnRotate(wxRibbonButtonBarEvent& e);

	void OnScale(wxRibbonButtonBarEvent& e);

	void OnSelectedDelete(wxRibbonButtonBarEvent& e);


	void OnCreateSurface(wxRibbonButtonBarEvent& e);

	void OnCreateSurfaceConfig(wxRibbonButtonBarEvent& e);

	void OnGridConfig(wxRibbonButtonBarEvent& e);

	void OnMetaballConfig(wxRibbonButtonBarEvent& e);

	void OnWireFrameConfig(wxRibbonButtonBarEvent& e);

	void OnNormalConfig(wxRibbonButtonBarEvent& e);

	void OnPhongConfig(wxRibbonButtonBarEvent& e);

	void OnLightConfig(wxRibbonButtonBarEvent& e);

	void OnCameraConfig(wxRibbonButtonBarEvent& e);

private:
	View* view;
	Model::MainModelSPtr<float> model;
	Model::MainConfig<float> config;

	void setRendering();

	void clear();
	
	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif