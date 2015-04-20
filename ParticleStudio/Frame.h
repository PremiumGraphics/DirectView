#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"

#include "Model.h"

#include <memory>

namespace Crystal {
	namespace CG {
		class View;
		class Model;
		class PolygonTree;
		class MaterialTree;
		class LightTree;

		class PolygonGroupProperty;
		class MaterialProperty;
		class LightProperty;

		class Frame;


class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

	Model& getModel() { return model; }

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


private:

private:

	View* view;
	Model model;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif