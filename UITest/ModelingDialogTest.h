#include "stdafx.h"

#include "../Math/Triangle.h"
#include "../Math/Quad.h"
#include "../Math/Circle.h"
#include "../Math/Sphere.h"
#include "../Math/Box.h"
#include "../Math/Cylinder.h"

#include "../Shader/WireFrameRenderer.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/PolygonBuilder.h"


namespace Crystal {
	namespace ModelingDialogTest {

class Frame;

class View : public wxGLCanvas
{
public:
	View(Frame *frame, const int width, const int height);

	~View();

	void buildDisplayList(const Graphics::PolygonSPtrList& polygons);

private:

	void OnPaint(wxPaintEvent&);

	void OnSize(wxSizeEvent& e);

	void draw(const wxSize& size);

private:
	wxGLContext glContext;

	void build();

	Shader::WireFrameRenderer wireFrameRenderer;

	Graphics::DisplayList dispList;

	wxDECLARE_NO_COPY_CLASS(View);
};

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

private:
	Math::Triangle triangle;
	Math::Quad quad;
	Math::Circle circle;
	Math::Sphere sphere;
	Math::Box box;
	Math::Cylinder cylinder;

	View* view;
	Graphics::PolygonSPtrList polygons;
	Graphics::PolygonBuilder builder;
};

	}
}