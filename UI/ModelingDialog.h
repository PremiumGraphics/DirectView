#ifndef __CRYSTAL_UI_MODELING_DIALOG_H__
#define __CRYSTAL_UI_MODELING_DIALOG_H__

#include "stdafx.h"

#include "../Math/Triangle.h"
#include "../Math/Quad.h"
#include "../Math/Cone.h"

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
	struct Config{
		int divideNumber;
		float radius;
		float height;

		Config() :
			divideNumber( 30),
			radius( 1.0 )
		{}
	};
	CylinderConfigDialog(wxWindow* parent);

	void setConfig(const Config& config);

	Config getConfig() const;

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
	CircleConfigDialog::Config circleConfig;
	SphereConfigDialog::Config sphereConfig;
	ConeConfigDialog::Config coneConfig;
	CylinderConfigDialog::Config cylinderConfig;
};

	}
}

#endif