#include "stdafx.h"

namespace ModelingDialogTest {

	class Frame : public wxFrame//wxMDIParentFrame
	{
	public:
		Frame();


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

	};

}