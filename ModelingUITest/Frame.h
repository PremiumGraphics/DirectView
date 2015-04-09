#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"

#include "Model.h"

#include "../UI/ModelingDialog.h"

#include "../UI/PropertyDialog.h"

#include "../UI/PolygonTree.h"

#include <memory>

namespace Crystal {
	namespace Modeling {
		class View;
		class Model;
		class MaterialTree;
		class LightTree;

		class MaterialProperty;
		class LightProperty;

		class Frame;

class Widgets {
public:
	Widgets() {}

	void build(Frame* parent, Model& model);

	void refresh() {
		polygonTree->build();
	}

	UI::PolygonTree* getPolygonTree() const { return polygonTree; }


	UI::PolygonProperty* getPolygonProperty() const { return polygonProperty; }

private:
	UI::PolygonTree* polygonTree;
	MaterialTree* materialTree;

	UI::PolygonProperty* polygonProperty;
};


class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

	Model& getModel() { return model; }

private:


	void OnCameraTranslate( wxRibbonButtonBarEvent& );

	void OnPolygonTranslate( wxRibbonButtonBarEvent& );

	void OnPolygonRotate( wxRibbonButtonBarEvent& );

	//void OnPick(wxRibbonButtonBarEvent&);


	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnLocale( wxCommandEvent& );

	void OnPolygonScale( wxRibbonButtonBarEvent& e);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );


	void clear();

private:

	Widgets w;

	UI::ModelingDialogs modelings;

	View* view;
	Model model;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif