#include "stdafx.h"

#include "ModelingDialogTest.h"

#include "../UI/PolygonTree.h"
#include "../UI/PropertyDialog.h"
#include "../Graphics/PolygonBuilder.h"
#include "../UI/ModelingDialog.h"


using namespace Crystal::ModelingDialogTest;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

enum {
	ID_CREATE_SPHERE = wxID_HIGHEST + 1,
	ID_CREATE_CYLINDER,
	ID_CREATE_BOX,
	ID_CREATE_CONE,
};

Frame::Frame()
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxEmptyString)
{
	wxRibbonBar* bar = new wxRibbonBar
		(
		this,
		wxNewId(),
		wxDefaultPosition,
		wxDefaultSize
		);

	bar->SetArtProvider(new wxRibbonAUIArtProvider);


	wxRibbonPage* page = new wxRibbonPage(bar, wxNewId(), wxT("Polygon"));
	//wxRibbonPanel* panel = new wxRibbonPanel( page, wxID_ANY, wxT("Polygon") );

	wxRibbonPanel* modelingPanel = new wxRibbonPanel(page, wxID_ANY, wxT("Modeling"));
	wxRibbonButtonBar* modelingBar = new wxRibbonButtonBar(modelingPanel);
	const int createTriangleId = wxNewId();
	const int createQuadId = wxNewId();
	const int createCircleId = wxNewId();
	modelingBar->AddHybridButton( createTriangleId, "Triangle", wxImage(32, 32));
	modelingBar->AddHybridButton( createQuadId, "Quad", wxImage(32, 32));
	modelingBar->AddHybridButton( createCircleId, "Circle", wxImage(32, 32));
	modelingBar->AddHybridButton(ID_CREATE_SPHERE, "Sphere", wxImage(32, 32));
	modelingBar->AddHybridButton(ID_CREATE_CYLINDER, "Cylinder", wxImage(32, 32));
	modelingBar->AddHybridButton(ID_CREATE_BOX, "Box", wxImage(32, 32));
	modelingBar->AddHybridButton(ID_CREATE_CONE, "Cone", wxImage(32, 32));

	Connect(createTriangleId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateTriangle));
	Connect(createTriangleId, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateTriangleConfig));
	Connect(createQuadId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateQuad));
	Connect(createQuadId, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateQuadConfig));
	Connect(createCircleId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCircle));
	Connect(createCircleId, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCircleConfig));
	Connect(ID_CREATE_SPHERE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateSphere));
	Connect(ID_CREATE_SPHERE, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateSphereConfig));
	Connect(ID_CREATE_CYLINDER, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCylinder));
	Connect(ID_CREATE_CYLINDER, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCylinderConfig));
	Connect(ID_CREATE_BOX, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateBox));
	Connect(ID_CREATE_BOX, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateBoxConfig));
	Connect(ID_CREATE_CONE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCone));
	Connect(ID_CREATE_CONE, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateConeConfig));

	bar->Realize();

	Show();
}


void Frame::OnCreateTriangle(wxRibbonButtonBarEvent& e)
{
	//const PolygonSPtr& polygon = model.getPolygonBuilder()->buildTriangle();
	//polygon->setName("Triangle");
	//w.getPolygonTree()->build();
}

void Frame::OnCreateTriangleConfig(wxRibbonButtonBarEvent& e)
{
	TriangleConfigDialog dialog(this, triangle);
	if (dialog.ShowModal() == wxID_OK) {
		triangle = dialog.get();
	}
}

void Frame::OnCreateQuad(wxRibbonButtonBarEvent& e)
{
	//const PolygonSPtr& polygon = model.getPolygonBuilder()->buildQuad();
	//polygon->setName("Quad");
	//w.getPolygonTree()->build();
}

void Frame::OnCreateQuadConfig(wxRibbonButtonBarEvent& e)
{
	QuadConfigDialog dialog(this, quad);
	if (dialog.ShowModal() == wxID_OK) {
		quad = dialog.get();
	}
}

void Frame::OnCreateCircle(wxRibbonButtonBarEvent& e)
{
	/*
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildCircleByNumber(1.0f, modelings.circleConfig.getDivideNumber());
	polygon->setName("Circle");
	w.getPolygonTree()->build();
	*/
}

void Frame::OnCreateCircleConfig(wxRibbonButtonBarEvent& e)
{
	CircleConfigDialog dialog(this);
	//dialog.setConfig(modelings.circleConfig);
	if (dialog.ShowModal() == wxID_OK) {
		//modelings.circleConfig = dialog.getConfig();
	}
}

void Frame::OnCreateSphere(wxRibbonButtonBarEvent& e)
{
	/*
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildSphere(modelings.sphereConfig.getUDivideNumber(), modelings.sphereConfig.getVDivideNumber());
	polygon->setName("Sphere");
	w.getPolygonTree()->build();
	*/
}

void Frame::OnCreateSphereConfig(wxRibbonButtonBarEvent& e)
{
	//const int num = wxGetNumberFromUser("Divide Number", wxEmptyString, wxEmptyString, 3, 360);
	SphereConfigDialog dialog(this);
	//dialog.setConfig(modelings.sphereConfig);
	if (dialog.ShowModal() == wxID_OK) {
		//modelings.sphereConfig = dialog.getConfig();
	}
}

void Frame::OnCreateCylinder(wxRibbonButtonBarEvent& e)
{
	//Cylinder c;
	//const PolygonSPtr& polygon = model.getPolygonBuilder()->build(modelings.cylinderConfig.divideNumber, c);
	//polygon->setName("Cylinder");
	//w.getPolygonTree()->build();
}

void Frame::OnCreateCylinderConfig(wxRibbonButtonBarEvent& e)
{
	CylinderConfigDialog dialog(this);
	//dialog.setConfig(modelings.cylinderConfig);
	if (dialog.ShowModal() == wxID_OK) {
		//modelings.cylinderConfig = dialog.getConfig();
	}
}

void Frame::OnCreateBox(wxRibbonButtonBarEvent& e)
{
	//const PolygonSPtr& polygon = model.getPolygonBuilder()->buildBox();
	//polygon->setName("Box");
	//w.getPolygonTree()->build();
}

void Frame::OnCreateBoxConfig(wxRibbonButtonBarEvent& e)
{
	BoxConfigDialog dialog(this, box);
	if (dialog.ShowModal() == wxID_OK) {
		box = dialog.get();
	}
}

void Frame::OnCreateCone(wxRibbonButtonBarEvent& e)
{
	//model.getPolygonBuilder()->build(modelings.coneConfig.divideNumber, modelings.coneConfig.cone);
	//w.getPolygonTree()->build();
}

void Frame::OnCreateConeConfig(wxRibbonButtonBarEvent& e)
{
	ConeConfigDialog dialog(this);
	//dialog.setConfig(modelings.coneConfig);
	if (dialog.ShowModal() == wxID_OK) {
		//modelings.coneConfig = dialog.getConfig();
	}
}