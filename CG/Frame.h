#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"
#include "../Graphics/PolygonBuilder.h"
#include "../IO/PolygonFactory.h"

#include "ModelingDialog.h"

#include "PropertyDialog.h"

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

class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

	Graphics::Camera<float>* getCamera() { return &camera; }

	Graphics::PolygonSPtrList getPolygons() const { return builder->getPolygons(); }

	Graphics::LightSPtrList getLights() { return lights; }

	Graphics::MaterialSPtrList getMaterials() { return builder->getMaterialBuilder()->getMaterials(); }

	Graphics::VertexSPtrVector getVertices() const { return builder->getVertices(); }

	Graphics::FaceSPtrVector getFaces() const { return builder->getFaces(); }

	void setSelectedVertex(const unsigned int id)
	{
		selectedVertex.clear();
		if (id >= 0 && id < getVertices().size()) {
			const Graphics::VertexSPtr& v = getVertices()[id];
			selectedVertex.push_back( v );
			//VertexPropertyDialog* dialog = new VertexPropertyDialog(this, *v);
			//dialog->Show();
		}
	}

	void setSelectedFace(const unsigned int id)
	{
		selectedFace.clear();
		if (id >= 0 && id < getFaces().size()) {
			std::shared_ptr< Graphics::Face > f = getFaces()[id];
			selectedFace.push_back( f );
			//FacePropertyDialog* dialog = new FacePropertyDialog(this, *f);
			//dialog->Show();
		}
	}


	Graphics::VertexSPtrVector getSelectedVertex() const { return selectedVertex; }

	Graphics::FaceSPtrVector getSelectedFace() const { return selectedFace; }

	void addPolygon(const Graphics::PolygonSPtr& polygon);

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

	void OnPolygonTranslate( wxRibbonButtonBarEvent& );

	void OnPolygonRotate( wxRibbonButtonBarEvent& );

	void OnPolygonRotateX(wxRibbonButtonBarEvent&);

	void OnPolygonRotateY(wxRibbonButtonBarEvent&);

	void OnPolygonRotateZ(wxRibbonButtonBarEvent&);

	//void OnPick(wxRibbonButtonBarEvent&);

	void OnAbout( wxRibbonButtonBarEvent& );

	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnLocale( wxCommandEvent& );

	void OnPolygonScale( wxRibbonButtonBarEvent& e);

	void OnWireFrame( wxRibbonButtonBarEvent& e);

	void OnPhong( wxRibbonButtonBarEvent& );

	void OnFlat( wxRibbonButtonBarEvent& );

	void OnNormal(wxRibbonButtonBarEvent&);

	void OnPoint(wxRibbonButtonBarEvent&);

	void OnID(wxRibbonButtonBarEvent&);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void OnCreateQuad(wxRibbonButtonBarEvent& e);

	void OnCreateQuadConfig(wxRibbonButtonBarEvent& e);

	void OnCreateTriangle(wxRibbonButtonBarEvent& e);

	void OnCreateTriangleConfig(wxRibbonButtonBarEvent& e);

	void OnCreateCircle(wxRibbonButtonBarEvent& e);

	void OnCreateCircleConfig(wxRibbonButtonBarEvent& e);

	void OnCreateSphere(wxRibbonButtonBarEvent& e);

	void OnCreateSphereConfig(wxRibbonButtonBarEvent& e);

	void OnCreateCylinder(wxRibbonButtonBarEvent& e);

	void OnCreateCylinderConfig(wxRibbonButtonBarEvent& e);

	void OnCreateBox(wxRibbonButtonBarEvent& e);

	void OnCreateBoxConfig(wxRibbonButtonBarEvent& e);

	void OnCreateCone(wxRibbonButtonBarEvent& e);

	void OnCreateConeConfig(wxRibbonButtonBarEvent& e);

	void OnDropDown(wxRibbonButtonBarEvent& e);

	void clear();

private:

	//wxTreeCtrl* tree;
	PolygonTree* polygonTree;
	MaterialTree* materialTree;
	LightTree* lightTree;

	PolygonProperty* polygonProperty;
	MaterialProperty* materialProperty;
	LightProperty* lightProperty;

	TriangleConfigDialog::Config triangleConfig;
	QuadConfigDialog::Config quadConfig;
	CircleConfigDialog::Config circleConfig;
	SphereConfigDialog::Config sphereConfig;
	BoxConfigDialog::Config boxConfig;
	ConeConfigDialog::Config coneConfig;
	CylinderConfigDialog::Config cylinderConfig;

	const Graphics::PolygonBuilderSPtr builder;

	Graphics::VertexSPtrVector selectedVertex;
	Graphics::FaceSPtrVector selectedFace;

	View* view;

	wxLocale locale;

	Graphics::Camera<float> camera;
	Graphics::LightSPtrList lights;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif