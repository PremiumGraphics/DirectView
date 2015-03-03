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
		Config() :
			divideNumber(3),
			width( 1.0),
			height( 1.0)
		{}

		void setDivideAngle(const float angle) { divideNumber = 360.0f / angle; }

		void setDivideNumber(const unsigned int divideNumber) { this->divideNumber = divideNumber; }

		unsigned int getDivideNumber() const { return divideNumber; }

		float getDivideAngle() const { return 360.0f / divideNumber; }

		void setWidth(const float width) { this->width = width;  }

		void setHeight(const float height) { this->height = height; }

		float getWidth() const { return width; }

		float getHeight() const { return height; }

		bool isValid() const {
			return
				divideNumber >= 3 &&
				width >= 0.0f &&
				height >= 0.0f;
		}

	private:
		unsigned int divideNumber;
		float width;
		float height;
	};


	CircleConfigDialog(wxWindow* parent) :
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

	void setConfig(const Config& config) {
		divideNumber->SetValue(config.getDivideNumber());
		divideAngle->SetValue(360.0f / config.getDivideNumber() );
		width->SetValue(config.getWidth());
		height->SetValue(config.getHeight());
	}

	Config getConfig() const {
		Config config;
		config.setDivideNumber( divideNumber->GetValue() );
		config.setWidth(width->GetValue());
		config.setHeight(height->GetValue());
		return config;
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
	struct Config {
		Config() :
			uDivideNumber( 3 ),
			vDivideNumber( 3 ),
			uRadius( 1.0f ),
			vRadius( 1.0f )
		{}

		float getUDivideNumber() const { return uDivideNumber; }

		void setUDivideNumber(const int uDivideNumber) { this->uDivideNumber = uDivideNumber; }

		float getVDivideNumber() const { return vDivideNumber; }

		void setVDivideNumber(const int vDivideNumber) { this->vDivideNumber = vDivideNumber; }

		float getURadius() const { return uRadius; }

		float getVRadius() const { return vRadius; }

		void setURadius(const float uRadius) { this->uRadius = uRadius; }

		void setVRadius(const float vRadius) { this->vRadius = vRadius; }

		bool isValid() const {
			return
				uDivideNumber >= 3 &&
				vDivideNumber >= 3 &&
				uRadius > 0.0f &&
				vRadius > 0.0f;
		}

	private:
		unsigned int uDivideNumber;
		unsigned int vDivideNumber;
		float uRadius;
		float vRadius;
	};

	SphereConfigDialog(wxWindow* parent) :
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

	void setConfig(const Config& config) {
		uDivideAngle->SetValue( config.getUDivideNumber() );
		vDivideAngle->SetValue( config.getVDivideNumber() );
		uRadius->SetValue(config.getURadius());
		vRadius->SetValue(config.getVRadius());
	}

	Config getConfig() const {
		Config config;
		config.setUDivideNumber(config.getUDivideNumber());
		config.setVDivideNumber(config.getVDivideNumber());
		config.setURadius(config.getURadius());
		config.setVRadius(config.getVRadius());
		return config;
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
			divideNumber( 3),
			radius( 1.0f),
			height( 1.0f)
			{}

		int divideNumber;
		float radius;
		float height;
	};

	ConeConfigDialog(wxWindow* parent) :
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

	Config getConfig() const {
		Config config;
		config.divideNumber = divideNumber->GetValue();
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