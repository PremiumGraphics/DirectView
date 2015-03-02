#ifndef __CRYSTAL_APP_MODELING_DIALOG_H__
#define __CRYSTAL_APP_MODELING_DIALOG_H__

#include "stdafx.h"

namespace Crystal{
	namespace CG {

class QuadConfigDialog : public wxDialog
{
public:
	struct Config{
		float xLength;
		float yLength;
	};

	QuadConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "QuadConfig", wxDefaultPosition, wxSize(500, 500))
	{
		/*
		new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 100));
		divideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 200));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
		*/
	}

	void setConfig(const Config& config) {
		this->xLength->SetValue(config.xLength);
		this->yLength->SetValue(config.yLength);
	}

	Config getConfig() {
		Config config;
		config.xLength = xLength->GetValue();
		config.yLength = yLength->GetValue();
	}

private:
	wxSpinCtrlDouble* xLength;
	wxSpinCtrlDouble* yLength;
};


class CircleConfigDialog : public wxDialog
{
public:
	CircleConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "CircleConfig", wxDefaultPosition, wxSize(500, 500))
	{
		new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 100));
		divideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 200));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	}

	void set(const float u) {
		divideAngle->SetValue(u);
	}

	float getDivideAngle() const { return divideAngle->GetValue(); }

	int getDivideNumber() const { return divideNumber->GetValue(); }

private:
	wxSpinCtrlDouble* divideAngle;
	wxSpinCtrl* divideNumber;
};


class SphereConfigDialog : public wxDialog
{
public:
	SphereConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "SphereConfig", wxDefaultPosition, wxSize(500, 500))
	{
		new wxStaticText(this, wxID_ANY, " U Divide", wxPoint(0, 100));
		uDivideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
		vDivideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	}

	void set(const float u, const float v) {
		uDivideAngle->SetValue(u);
		vDivideAngle->SetValue(v);
	}

	float getUDivideAngle() const { return uDivideAngle->GetValue(); }

	float getVDivideAngle() const { return vDivideAngle->GetValue(); }

private:
	wxSpinCtrlDouble* uDivideAngle;
	wxSpinCtrlDouble* vDivideAngle;

	wxSpinCtrl uDivide;
};

class ConeCreateConfigDialog : public wxDialog
{
public:

private:
};

class CylinderConfigDialog : public wxDialog
{
public:
	CylinderConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "CylinderConfig", wxDefaultPosition, wxSize(500,500))
	{
		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 200));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
	}

	int getDivideNumber() const { return divideNumber->GetValue(); }

private:
	wxSpinCtrl* divideNumber;
};

	}
}

#endif