#ifndef __CRYSTAL_UI_RENDERING_DIALOG_H__
#define __CRYSTAL_UI_RENDERING_DIALOG_H__

#include "stdafx.h"

namespace Crystal {
	namespace Graphics {

class WireframeConfigDialog : public wxDialog
{
public:
	WireframeConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "RenderingConfig", wxDefaultPosition, wxSize( 700, 700 ) )
	{
		new wxStaticText(this, wxID_ANY, "PointSize", wxPoint(0, 100));
		pointSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));
		pointSize->SetRange(1.0, 100.0);

		new wxStaticText(this, wxID_ANY, "LineWidth", wxPoint(0, 200));
		lineWidth = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxStaticText(this, wxID_ANY, "BoundingBox", wxPoint(0, 300));
		drawBB = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(100, 300) );

		new wxStaticText(this, wxID_ANY, "Plane", wxPoint(0, 400));
		drawPlane = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(100, 400));

		new wxStaticText(this, wxID_ANY, "Surface", wxPoint(300, 100));
		drawSurface = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(400, 100));

		new wxStaticText(this, wxID_ANY, "Metaball", wxPoint(300, 300));
		drawMetaball = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(400, 200));

		new wxStaticText(this, wxID_ANY, "Volume", wxPoint(300, 400));
		drawVolume = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(400, 300));

		new wxButton( this, wxID_OK, "OK", wxPoint(300,500) );
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(400, 500));
	}

	void set(const Model::RenderingConfig<float>& config) {
		pointSize->SetValue(config.pointSize );
		lineWidth->SetValue( config.lineWidth );
		drawBB->SetValue( config.drawBB );
		drawPlane->SetValue( config.drawPlane_ );
		drawSurface->SetValue(config.drawSurface);
		drawMetaball->SetValue(config.drawMetaball);
		drawVolume->SetValue(config.drawVolume);
	}

	Model::RenderingConfig<float> get() {
		Model::RenderingConfig<float> config;
		config.pointSize = pointSize->GetValue();
		config.lineWidth = lineWidth->GetValue();
		config.drawBB = drawBB->GetValue();
		config.drawPlane_ = drawPlane->GetValue();
		config.drawSurface = drawSurface->GetValue();
		config.drawMetaball = drawMetaball->GetValue();
		config.drawVolume = drawVolume->GetValue();
		return config;
	}

private:
	wxSpinCtrlDouble* pointSize;
	wxSpinCtrlDouble* lineWidth;
	wxCheckBox* drawBB;
	wxCheckBox* drawPlane;
	wxCheckBox* drawSurface;
	wxCheckBox* drawVolume;
	wxCheckBox* drawMetaball;
};

	}
}

#endif