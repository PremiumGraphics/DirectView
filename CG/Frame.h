#ifndef __CRYSTAL_UI_FRAME_H__
#define __CRYSTAL_UI_FRAME_H__

#include "../Command/MainFactory.h"
#include "../Command/MainCommand.h"

#include <memory>

namespace Crystal {
	namespace Command {
		class MainFactory;
	}
	namespace UI {
		class View;

class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

	Command::MainFactory& getModel() { return model; }

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

	void OnLocale( wxCommandEvent& );

	void OnWireFrame( wxRibbonButtonBarEvent& e);

	void OnPhong( wxRibbonButtonBarEvent& );

	void OnFlat( wxRibbonButtonBarEvent& );

	void OnNormal(wxRibbonButtonBarEvent&);

	void OnPoint(wxRibbonButtonBarEvent&);

	void OnID(wxRibbonButtonBarEvent&);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void clear();


	void OnCreateSphere(wxRibbonButtonBarEvent& e);

	void OnCreateCylinder(wxRibbonButtonBarEvent& e);

	void OnCreateBox(wxRibbonButtonBarEvent& e);

	void OnCreateCone(wxRibbonButtonBarEvent& e);


	void OnBooleanUnion(wxRibbonButtonBarEvent& e);

	void OnBooleanDiff(wxRibbonButtonBarEvent& e);

	void OnBooleanIntersection(wxRibbonButtonBarEvent& e);

	void OnBooleanNot(wxRibbonButtonBarEvent& e);


private:
	View* view;
	Command::MainFactory model;
	Command::MainCommand command;
	
	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif