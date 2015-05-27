#include "stdafx.h"
#include "ModelingDialog.h"

using namespace Crystal::Math;
using namespace Crystal::CG;


SphereConfigDialog::SphereConfigDialog(wxWindow* parent, const Sphere<float>& s) :
wxDialog(parent, wxID_ANY, "SphereConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "U Divide", wxPoint(0, 100));
	uDivideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
	new wxStaticText(this, wxID_ANY, "V Divide", wxPoint(0, 200));
	vDivideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	new wxStaticText(this, wxID_ANY, "U Radius", wxPoint(0, 300));
	uRadius = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));
	new wxStaticText(this, wxID_ANY, "V Radius", wxPoint(0, 400));
	vRadius = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 400));

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}


BoxConfigDialog::BoxConfigDialog(wxWindow* parent, const Box& box) :
wxDialog(parent, wxID_ANY, "BoxConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "X Size", wxPoint(0, 100));
	xSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
	xSize->SetRange(0.0, 10000.0);

	new wxStaticText(this, wxID_ANY, "Y Size", wxPoint(0, 200));
	ySize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	ySize->SetRange(0.0, 10000.0);

	new wxStaticText(this, wxID_ANY, "Z Size", wxPoint(0, 300));
	zSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));
	zSize->SetRange(0.0, 10000.0);

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));

	//xSize->SetValue(box.xSize);
	//ySize->SetValue(box.ySize);
	//zSize->SetValue(config.zSize);

}

Box BoxConfigDialog::get() const
{
	return Box();
}

CylinderConfigDialog::CylinderConfigDialog(wxWindow* parent, const Cylinder<float>& cylinder) :
wxDialog(parent, wxID_ANY, "CylinderConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 100));
	divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

	new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 200));

	new wxStaticText(this, wxID_ANY, "Radius", wxPoint(0, 300));
	radius = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));

	new wxStaticText(this, wxID_ANY, "Height", wxPoint(0, 400));
	height = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 400));

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}


Cylinder<float> CylinderConfigDialog::get() const
{
	return Cylinder<float>();
}
