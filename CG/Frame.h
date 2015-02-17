#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "Model.h"

#include <memory>

namespace Crystal {
	namespace CG {
		class View;
		class Model;
		class PolygonTree;
		class MaterialTree;
		class LightTree;

		class PolygonProperty;
		class MaterialProperty;
		class LightProperty;
		class ParticleProperty;
		class TextureProperty;

class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame(Model* model);

	~Frame();

	Model* getModel() const { return model; }

private:
	void OnNew( wxRibbonToolBarEvent& );

	void OnClose( wxRibbonToolBarEvent& );

	void OnFileOpen( wxRibbonToolBarEvent& e );

	void OnFileSave( wxRibbonToolBarEvent& );

	void OnFileSaveAs( wxRibbonToolBarEvent& e );

	void OnImport( wxRibbonToolBarEvent& e );

	void OnExport( wxRibbonToolBarEvent& e);

	void OnCameraTranslate( wxRibbonToolBarEvent& );

	void OnLightTranslate( wxRibbonToolBarEvent& );

	void OnPolygonTranslate( wxRibbonToolBarEvent& );

	void OnPolygonRotate( wxRibbonToolBarEvent& );

	void OnAbout( wxRibbonToolBarEvent& );

	void OnGLConfig( wxRibbonToolBarEvent& e );

	void OnLocale( wxCommandEvent& );

	void OnPolygonScale( wxRibbonToolBarEvent& );

	void OnWireFrame( wxRibbonToolBarEvent& );

	void OnPhong( wxRibbonToolBarEvent& );

	void OnFlat( wxRibbonToolBarEvent& );

	void OnCameraFit( wxRibbonToolBarEvent& e );

	void OnCapture( wxRibbonToolBarEvent& e );

private:
	Model* model;

	//wxTreeCtrl* tree;
	PolygonTree* polygonTree;
	MaterialTree* materialTree;
	LightTree* lightTree;

	PolygonProperty* polygonProperty;
	MaterialProperty* materialProperty;
	LightProperty* lightProperty;

	View* view;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif