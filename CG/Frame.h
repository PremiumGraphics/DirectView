#ifndef __CRYSTAL_UI_FRAME_H__
#define __CRYSTAL_UI_FRAME_H__

#include "../Command/MainFactory.h"
#include "../Command/MainCommand.h"
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

	Command::MainFactory<float>& getModel() { return factory; }

private:
	void OnNew( wxRibbonButtonBarEvent& );

	void OnClose( wxRibbonButtonBarEvent& );

	void OnFileOpen( wxRibbonButtonBarEvent& e );

	void OnFileSave( wxRibbonButtonBarEvent& );

	void OnFileSaveAs( wxRibbonButtonBarEvent& e );

	void OnImport( wxRibbonButtonBarEvent& e );

	void OnExport( wxRibbonButtonBarEvent& e);

	void OnCameraTranslate( wxRibbonButtonBarEvent& );

	void OnLightTranslate( wxRibbonButtonBarEvent& );

	//void OnPick(wxRibbonButtonBarEvent&);

	void OnAbout( wxRibbonButtonBarEvent& );

	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnWireFrame( wxRibbonButtonBarEvent& e);

	void OnPhong( wxRibbonButtonBarEvent& );

	void OnFlat( wxRibbonButtonBarEvent& );

	void OnNormal(wxRibbonButtonBarEvent&);

	void OnPoint(wxRibbonButtonBarEvent&);

	void OnID(wxRibbonButtonBarEvent&);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void clear();


	void OnCreateMetaball(wxRibbonButtonBarEvent& e);

	void OnCreateCylinder(wxRibbonButtonBarEvent& e);

	void OnCreateBox(wxRibbonButtonBarEvent& e);

	void OnCreateGrid(wxRibbonButtonBarEvent& e);


	void OnBooleanUnion(wxRibbonButtonBarEvent& e);

	void OnBooleanDiff(wxRibbonButtonBarEvent& e);

	void OnBooleanIntersection(wxRibbonButtonBarEvent& e);

	void OnBooleanNot(wxRibbonButtonBarEvent& e);

	void OnSpaceTransform(wxRibbonButtonBarEvent& e);

	void OnCreatePolygon(wxRibbonButtonBarEvent& e);

	void OnGridConfig(wxRibbonButtonBarEvent& e);

	void OnMetaballConfig(wxRibbonButtonBarEvent& e);

	void OnWireFrameConfig(wxRibbonButtonBarEvent& e);

	void OnNormalConfig(wxRibbonButtonBarEvent& e);

	void OnPhongConfig(wxRibbonButtonBarEvent& e);

	void OnPointConfig(wxRibbonButtonBarEvent& e);

	void setRendering();

private:
	View* view;
	Command::MainFactory<float> factory;
	Command::MainCommand command;
	Command::MainConfig<float> config;
	
	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif