#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"

#include "Model.h"

#include "ModelingDialog.h"

#include "PropertyDialog.h"

#include "Tree.h"
#include "PropertyDialog.h"

#include "../Math/Triangle.h"
#include "../Math/Quad.h"
#include "../Math/Circle.h"
#include "../Math/Sphere.h"
#include "../Math/Box.h"
#include "../Math/Cylinder.h"


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

		class Frame;

class Widgets {
public:
	Widgets() {}

	void build(Frame* parent, Model& model);

	void refresh() {
		materialTree->build();
		lightTree->build();
	}

	MaterialTree* getMaterialTree() const { return materialTree; }

	LightTree* getLightTree() const { return lightTree; }

	PolygonProperty* getPolygonProperty() const { return polygonProperty; }

	MaterialProperty* getMaterialProperty() const { return materialProperty; }

	LightProperty* getLightProperty() const { return lightProperty; }

private:
	MaterialTree* materialTree;
	LightTree* lightTree;

	PolygonProperty* polygonProperty;
	MaterialProperty* materialProperty;
	LightProperty* lightProperty;
};


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

	void clear();

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

private:
	Math::Triangle triangle;
	Math::Quad quad;
	Math::Circle circle;
	Math::Sphere sphere;
	Math::Box box;
	Math::Cylinder cylinder;
	Math::Cone cone;


private:

	Widgets w;

	View* view;
	Model model;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif