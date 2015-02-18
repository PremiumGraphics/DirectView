#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"
#include "../IO/PolygonFactory.h"

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
	Frame();

	~Frame();

	Graphics::Camera<float>* getCamera() { return &camera; }

	std::list<Graphics::Polygon*> getPolygons() const { return polygons; }

	std::list<Graphics::Light*>* getLights() { return &lights; }

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

	void clear();

private:

	//wxTreeCtrl* tree;
	PolygonTree* polygonTree;
	MaterialTree* materialTree;
	LightTree* lightTree;

	PolygonProperty* polygonProperty;
	MaterialProperty* materialProperty;
	LightProperty* lightProperty;

	View* view;

	wxLocale locale;

	Graphics::Camera<float> camera;
	std::list<Graphics::Polygon*> polygons;
	std::list<Graphics::Material*> materials;
	std::list<Graphics::Light*> lights;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif