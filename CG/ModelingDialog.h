#ifndef __CRYSTAL_APP_MODELING_DIALOG_H__
#define __CRYSTAL_APP_MODELING_DIALOG_H__

#include "stdafx.h"

namespace Crystal{
	namespace CG {

class TriangleConfigDialog : public wxDialog
{
public:
	struct Config {
		Config() : xSize(1.0), ySize( 1.0)
		{}
		float xSize;
		float ySize;
	};

	TriangleConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "QuadConfig", wxDefaultPosition, wxSize(500, 500))
	{
		new wxStaticText(this, wxID_ANY, "X Size", wxPoint(0, 100));
		xSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "Y Size", wxPoint(0, 200));
		ySize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
	}

	void setConfig(const Config& config) {
		xSize->SetValue(config.xSize);
		ySize->SetValue(config.ySize);
	}

	Config getConfig() const {
		Config config;
		config.xSize = xSize->GetValue();
		config.ySize = ySize->GetValue();
		return config;
	}

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
};

class QuadConfigDialog : public wxDialog
{
public:
	struct Config{
		float xSize;
		float ySize;
	};

	QuadConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "QuadConfig", wxDefaultPosition, wxSize(500, 500))
	{
		new wxStaticText(this, wxID_ANY, "X Size", wxPoint(0, 100));
		xSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "Y Size", wxPoint(0, 200));
		ySize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
	}

	void setConfig(const Config& config) {
		this->xSize->SetValue(config.xSize);
		this->ySize->SetValue(config.ySize);
	}

	Config getConfig() {
		Config config;
		config.xSize = xSize->GetValue();
		config.ySize = ySize->GetValue();
		return config;
	}

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
};


class CircleConfigDialog : public wxDialog
{
public:
	struct Config{
		unsigned int divideNumber;
	};


	CircleConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "CircleConfig", wxDefaultPosition, wxSize(500, 500))
	{
		new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 100));
		divideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 200));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
	}

	void setConfig(const Config& config) {
		divideAngle->SetValue(360.0 / config.divideNumber);
	}

	Config getConfig() const {
		Config config;
		config.divideNumber = divideNumber->GetValue();
	}

private:
	wxSpinCtrlDouble* divideAngle;
	wxSpinCtrl* divideNumber;
};


class SphereConfigDialog : public wxDialog
{
public:
	struct Config {
		float getUDivideNumber() const { return uDivideNumber; }

		void setUDivideNumber(const int uDivideNumber) { this->uDivideNumber = uDivideNumber; }

		float getVDivideNumber() const { return vDivideNumber; }

		void setVDivideNumber(const int vDivideNumber) { this->vDivideNumber = vDivideNumber; }

	private:
		unsigned int uDivideNumber;
		unsigned int vDivideNumber;
	};

	SphereConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "SphereConfig", wxDefaultPosition, wxSize(500, 500))
	{
		new wxStaticText(this, wxID_ANY, "U Divide", wxPoint(0, 100));
		uDivideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
		new wxStaticText(this, wxID_ANY, "V Divide", wxPoint(0, 200));
		vDivideAngle = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
	}

	void setConfig(const Config& config) {
		uDivideAngle->SetValue( config.getUDivideNumber() );
		vDivideAngle->SetValue( config.getVDivideNumber() );
	}

private:
	wxSpinCtrlDouble* uDivideAngle;
	wxSpinCtrlDouble* vDivideAngle;

	wxSpinCtrl* uDivideNumber;
	wxSpinCtrl* vDivideNumber;
};

class ConeCreateConfigDialog : public wxDialog
{
public:
	struct Config {
		Config() :
			divideNumber( 3),
			radius( 1.0f),
			height( 1.0f)
			{}

		int divideNumber;
		float radius;
		float height;
	};

	ConeCreateConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "ConeConfig", wxDefaultPosition, wxSize( 500, 500))
	{
		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 100));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
	}

	void setConfig(const Config& config) {
		divideNumber->SetValue(config.divideNumber);
	}

private:
	wxSpinCtrl* divideNumber;
	wxSpinCtrlDouble* radius;
	wxSpinCtrlDouble* height;
};

class CylinderConfigDialog : public wxDialog
{
public:
	struct Config{
		float divideNumber;
	};
	CylinderConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "CylinderConfig", wxDefaultPosition, wxSize(500,500))
	{
		new wxStaticText(this, wxID_ANY, "Divide Number", wxPoint(0, 100));
		divideNumber = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "Divide Angle", wxPoint(0, 200));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
	}

	void setConfig(const Config& config) {
		this->divideNumber->SetValue( config.divideNumber );
	}

	Config getConfig() const {
		Config config;
		config.divideNumber = divideNumber->GetValue();
		return config;
	}

private:
	wxSpinCtrl* divideNumber;
};

class BoxConfigDialog : public wxDialog
{
public:
	struct Config{
		Config() :
			xSize(1.0), ySize(1.0), zSize( 1.0)
		{}
		float xSize;
		float ySize;
		float zSize;
	};

	BoxConfigDialog(wxWindow* parent) :
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

	void setConfig(const Config& config) {
		xSize->SetValue(config.xSize);
		ySize->SetValue(config.ySize);
		zSize->SetValue(config.zSize);
	}

	Config getConfig() const {
		Config config;
		config.xSize = xSize->GetValue();
		config.ySize = ySize->GetValue();
		config.zSize = zSize->GetValue();
		return config;
	}

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
	wxSpinCtrlDouble* zSize;
};

	}
}

#endif