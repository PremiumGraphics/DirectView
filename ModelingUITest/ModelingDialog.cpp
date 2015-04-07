#include "stdafx.h"
#include "ModelingDialog.h"

using namespace Crystal::Modeling;

TriangleConfigDialog::TriangleConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "QuadConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "X Size", wxPoint(0, 100));
	xSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
	xSize->SetValue(1.0);

	new wxStaticText(this, wxID_ANY, "Y Size", wxPoint(0, 200));
	ySize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	ySize->SetValue(1.0);

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}

void TriangleConfigDialog::setConfig(const Config& config)
{
	xSize->SetValue(config.xSize);
	ySize->SetValue(config.ySize);
}

TriangleConfigDialog::Config TriangleConfigDialog::getConfig() const
{
	Config config;
	config.xSize = xSize->GetValue();
	config.ySize = ySize->GetValue();
	return config;
}

QuadConfigDialog::QuadConfigDialog(wxWindow* parent) :
wxDialog(parent, wxID_ANY, "QuadConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "X Size", wxPoint(0, 100));
	xSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

	new wxStaticText(this, wxID_ANY, "Y Size", wxPoint(0, 200));
	ySize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}

void QuadConfigDialog::setConfig(const Config& config)
{
	this->xSize->SetValue(config.xSize);
	this->ySize->SetValue(config.ySize);
}

CircleConfigDialog::CircleConfigDialog(wxWindow* parent) :
wxDialog(parent, wxID_ANY, "CircleConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 100));
	divideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
	divideAngle->SetRange(0.1, 120.0);

	new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 200));
	divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	divideNumber->SetRange(3, 360);

	new wxStaticText(this, wxID_ANY, "Width", wxPoint(0, 300));
	width = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));

	new wxStaticText(this, wxID_ANY, "Height", wxPoint(0, 400));
	height = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 400));

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}

SphereConfigDialog::SphereConfigDialog(wxWindow* parent) :
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


BoxConfigDialog::BoxConfigDialog(wxWindow* parent) :
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
}

void BoxConfigDialog::setConfig(const Config& config)
{
	xSize->SetValue(config.xSize);
	ySize->SetValue(config.ySize);
	zSize->SetValue(config.zSize);
}

BoxConfigDialog::Config BoxConfigDialog::getConfig() const
{
	Config config;
	config.xSize = xSize->GetValue();
	config.ySize = ySize->GetValue();
	config.zSize = zSize->GetValue();
	return config;
}

CylinderConfigDialog::CylinderConfigDialog(wxWindow* parent) :
wxDialog(parent, wxID_ANY, "CylinderConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 100));
	divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

	new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 200));

	new wxStaticText(this, wxID_ANY, "Width", wxPoint(0, 300));
	width = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));

	new wxStaticText(this, wxID_ANY, "Height", wxPoint(0, 400));
	height = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 400));

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}

void CylinderConfigDialog::setConfig(const Config& config)
{
	this->divideNumber->SetValue(config.divideNumber);
	this->width->SetValue(config.width);
	this->height->SetValue(config.height);
}

CylinderConfigDialog::Config CylinderConfigDialog::getConfig() const
{
	Config config;
	config.divideNumber = divideNumber->GetValue();
	config.width = width->GetValue();
	config.height = height->GetValue();
	return config;
}
