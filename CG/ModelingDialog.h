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

	TriangleConfigDialog(wxWindow* parent);

	void setConfig(const Config& config);

	Config getConfig() const;

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

	QuadConfigDialog(wxWindow* parent);

	void setConfig(const Config& config);

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


	CircleConfigDialog(wxWindow* parent);

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

	SphereConfigDialog(wxWindow* parent);

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

	BoxConfigDialog(wxWindow* parent);

	void setConfig(const Config& config);

	Config getConfig() const;

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
	wxSpinCtrlDouble* zSize;
};

struct ModelingDialogs {
	TriangleConfigDialog::Config triangleConfig;
	QuadConfigDialog::Config quadConfig;
	CircleConfigDialog::Config circleConfig;
	SphereConfigDialog::Config sphereConfig;
	BoxConfigDialog::Config boxConfig;
	ConeConfigDialog::Config coneConfig;
	CylinderConfigDialog::Config cylinderConfig;
};

	}
}

#endif