#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"

#include "../IO/Model.h"

#include <memory>

namespace Crystal {
	namespace CG {
		class View;
		class Frame;
		class ParticleTree;

class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

	IO::Model& getModel() { return model; }

private:
	void OnNew( wxRibbonButtonBarEvent& );

	void OnClose( wxRibbonButtonBarEvent& );

	void OnFileOpen( wxRibbonButtonBarEvent& e );

	void OnFileSave( wxRibbonButtonBarEvent& );

	void OnFileSaveAs( wxRibbonButtonBarEvent& e );

	void OnImport( wxRibbonButtonBarEvent& e );

	void OnExport( wxRibbonButtonBarEvent& e);

	void OnCameraTranslate( wxRibbonButtonBarEvent& );


	//void OnPick(wxRibbonButtonBarEvent&);

	void OnAbout( wxRibbonButtonBarEvent& );

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void clear();

	void OnCreateSphere(wxRibbonButtonBarEvent& e);

	void OnCreateCylinder(wxRibbonButtonBarEvent& e);

	void OnCreateBox(wxRibbonButtonBarEvent& e);

	void OnCreateCone(wxRibbonButtonBarEvent& e);

	void OnGraphicsSetting(wxRibbonButtonBarEvent& e);

	void OnCreateUnion(wxRibbonButtonBarEvent& e);

	void OnCreateDiff(wxRibbonButtonBarEvent& e);

	void OnCreateIntersection(wxRibbonButtonBarEvent& e);

	void OnCalculateVolume(wxRibbonButtonBarEvent& e);

	void OnCalculateMass(wxRibbonButtonBarEvent& e);

	void OnCheckIntersection(wxRibbonButtonBarEvent& e);

private:

private:

	View* view;
	IO::Model model;

	ParticleTree* particleTree;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif