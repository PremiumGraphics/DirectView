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


View::View(Frame* parent, const int width, const int height)
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint(0, 0), wxSize(width, height), wxFULL_REPAINT_ON_RESIZE),
glContext(this)
{
	glContext.SetCurrent(*this);

	//	const int attributes[] = {WX_GL_SAMPLE_BUFFERS};
	//	bool b = IsDisplaySupported( attributes );

	Connect(wxEVT_PAINT, wxPaintEventHandler(View::OnPaint));
	//Connect( wxEVT_MOUSE_EVENTS, wxMouseEventHandler( View::onMouse ) );
	Connect(wxEVT_SIZE, wxSizeEventHandler(View::OnSize));

	build();

	//texture = new TextureObject( pixels, 2, 1 );
}

View::~View()
{
	//delete texture;
}

#include "../Math/Vector3d.h"

using namespace Crystal::Math;


void View::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);

	const wxSize size = GetClientSize();

	glContext.SetCurrent(*this);

	glViewport(0, 0, size.x, size.y);

	draw(size);

	glFlush();

	SwapBuffers();
}

void View::OnSize(wxSizeEvent& e)
{
	draw(e.GetSize());
}

void View::draw(const wxSize& size)
{
	const int width = size.GetWidth();
	const int height = size.GetHeight();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Camera<float> c;
	c.setNear(0.1f);
	c.move(Vector3d(0.0, 0.0, -5.0));

	glLineWidth(1.0f);
	wireFrameRenderer.render(width, height, c, dispList);
}

void View::build()
{
	wireFrameRenderer.build();
}

void View::buildDisplayList(const PolygonSPtrList& polygons)
{
	dispList.clear();
	for (const PolygonSPtr& p : polygons) {
		dispList.add(p);
	}
}

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

	view = new View(this, 512, 512);

	wxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

	vSizer->Add(bar, 0, wxEXPAND);
	vSizer->Add(view, 0, wxEXPAND);

	SetSizer(vSizer);

	bar->Realize();

	Show();
}


void Frame::OnCreateTriangle(wxRibbonButtonBarEvent& e)
{
	const Triangle t;
	builder.build(t);
	view->buildDisplayList(builder.getPolygons());
	view->Refresh();
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
	const Quad q;
	builder.build(q);
	view->buildDisplayList(builder.getPolygons());
	view->Refresh();

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
	builder.buildCircleByNumber( 1.0f, 180 );
	view->buildDisplayList(builder.getPolygons());
	view->Refresh();
}

void Frame::OnCreateCircleConfig(wxRibbonButtonBarEvent& e)
{
	CircleConfigDialog dialog(this, circle);
	//dialog.setConfig(modelings.circleConfig);
	if (dialog.ShowModal() == wxID_OK) {
		circle = dialog.get();
		//modelings.circleConfig = dialog.getConfig();
	}
}

void Frame::OnCreateSphere(wxRibbonButtonBarEvent& e)
{
	builder.build(sphere, 30, 30);
	view->buildDisplayList(builder.getPolygons());
	view->Refresh();
	/*
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildSphere(modelings.sphereConfig.getUDivideNumber(), modelings.sphereConfig.getVDivideNumber());
	polygon->setName("Sphere");
	w.getPolygonTree()->build();
	*/
}

void Frame::OnCreateSphereConfig(wxRibbonButtonBarEvent& e)
{
	SphereConfigDialog dialog(this, sphere);
	//dialog.setConfig(modelings.sphereConfig);
	if (dialog.ShowModal() == wxID_OK) {
		sphere = dialog.get();
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
	CylinderConfigDialog dialog(this, cylinder);
	if (dialog.ShowModal() == wxID_OK) {
		cylinder = dialog.get();
	}
}

void Frame::OnCreateBox(wxRibbonButtonBarEvent& e)
{
	const Box b;
	builder.build(b);
	view->buildDisplayList(builder.getPolygons());
	view->Refresh();
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
	builder.build(10, cone);
	view->buildDisplayList(builder.getPolygons());
	view->Refresh();
}

void Frame::OnCreateConeConfig(wxRibbonButtonBarEvent& e)
{
	ConeConfigDialog dialog(this);
	//dialog.setConfig(modelings.coneConfig);
	if (dialog.ShowModal() == wxID_OK) {
		//modelings.coneConfig = dialog.getConfig();
	}
}