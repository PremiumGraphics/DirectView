#ifndef __CRYSTAL_UI_MODELING_DIALOG_H__
#define __CRYSTAL_UI_MODELING_DIALOG_H__

#include "stdafx.h"

#include "../Math/Triangle.h"
#include "../Math/Quad.h"
#include "../Math/Cone.h"
#include "../Math/Circle.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

namespace Crystal{
	namespace UI {

class TriangleConfigDialog : public wxDialog
{
public:
	TriangleConfigDialog(wxWindow* parent, const Math::Triangle& t);

	Math::Triangle get() const;

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
};



class QuadConfigDialog : public wxDialog
{
public:
	QuadConfigDialog(wxWindow* parent, const Math::Quad& q);

	Math::Quad get(){
		return Math::Quad();
	}

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
};


class CircleConfigDialog : public wxDialog
{
public:

	CircleConfigDialog(wxWindow* parent, const Math::Circle& circle);

	Math::Circle get() const {
		return Math::Circle();
	}

private:
	wxSpinCtrlDouble* divideAngle;
	wxSpinCtrl* divideNumber;
	wxSpinCtrlDouble* width;
	wxSpinCtrlDouble* height;
};


class SphereConfigDialog : public wxDialog
{
public:
	
	SphereConfigDialog(wxWindow* parent, const Math::Sphere& sphere);

	Math::Sphere get() const {
		return Math::Sphere();
	}

private:
	wxSpinCtrlDouble* uDivideAngle;
	wxSpinCtrlDouble* vDivideAngle;

	wxSpinCtrl* uDivideNumber;
	wxSpinCtrl* vDivideNumber;

	wxSpinCtrlDouble* uRadius;
	wxSpinCtrlDouble* vRadius;
};

class ConeConfigDialog : public wxDialog
{
public:
	struct Config {
		Config() :
			divideNumber( 30)
			{}

		int divideNumber;
		Math::Cone cone;
	};

	ConeConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "ConeConfig", wxDefaultPosition, wxSize( 500, 500))
	{
		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 100));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));

		new wxStaticText(this, wxID_ANY, "Radius", wxPoint(0, 200));
		radius = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxStaticText(this, wxID_ANY, "Height", wxPoint(0, 300));
		height = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));
	}

	void setConfig(const Config& config) {
		divideNumber->SetValue(config.divideNumber);
		radius->SetValue(config.cone.getRadius());
		height->SetValue(config.cone.getHeight());
	}

	Config getConfig() const {
		Config config;
		config.divideNumber = divideNumber->GetValue();
		config.cone.setRadius( radius->GetValue() );
		config.cone.setHeight( height->GetValue() );
		return config;
	}

private:
	wxSpinCtrl* divideNumber;
	wxSpinCtrlDouble* radius;
	wxSpinCtrlDouble* height;
};

class CylinderConfigDialog : public wxDialog
{
public:
	CylinderConfigDialog(wxWindow* parent, const Math::Cylinder& cylinder);

	Math::Cylinder get() const;

private:
	wxSpinCtrl* divideNumber;
	wxSpinCtrl* radius;
	wxSpinCtrl* height;
};

class BoxConfigDialog : public wxDialog
{
public:

	BoxConfigDialog(wxWindow* parent, const Math::Box& box);

	Math::Box get() const;

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
	wxSpinCtrlDouble* zSize;
};

struct ModelingDialogs {
	ConeConfigDialog::Config coneConfig;
};

	}
}

#endif