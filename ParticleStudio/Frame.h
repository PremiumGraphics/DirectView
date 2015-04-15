#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"

#include "Model.h"

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

	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnPolygonScale( wxRibbonButtonBarEvent& e);

	void OnID(wxRibbonButtonBarEvent&);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );

	void clear();

	void OnCreateQuad(wxRibbonButtonBarEvent& e);

	void OnCreateTriangle(wxRibbonButtonBarEvent& e);

	void OnCreateCircle(wxRibbonButtonBarEvent& e);

	void OnCreateSphere(wxRibbonButtonBarEvent& e);

	void OnCreateCylinder(wxRibbonButtonBarEvent& e);

	void OnCreateBox(wxRibbonButtonBarEvent& e);

	void OnCreateCone(wxRibbonButtonBarEvent& e);

private:
	Math::Triangle triangle;
	Math::Quad quad;
	Math::Circle circle;
	Math::Sphere sphere;
	Math::Box box;
	Math::Cylinder cylinder;
	Math::Cone cone;


private:

	View* view;
	Model model;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif