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

		new wxStaticText(this, wxID_ANY, "Normal", wxPoint(300, 200));
		drawNormal = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(400, 200));


		new wxStaticText(this, wxID_ANY, "Volume", wxPoint(300, 300));
		drawVolume = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(400, 300));

		new wxStaticText(this, wxID_ANY, "Cells", wxPoint(300, 400));
		drawCells = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(400, 400));


		new wxButton( this, wxID_OK, "OK", wxPoint(300,500) );
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(400, 500));
	}

	void set(const Command::RenderingConfig<float>& config) {
		pointSize->SetValue(config.pointSize );
		lineWidth->SetValue( config.lineWidth );
		drawVolume->SetValue(config.drawVolume);
		drawCells->SetValue(config.drawCells);
		drawNormal->SetValue(config.drawNormal);
	}

	Command::RenderingConfig<float> get() {
		Command::RenderingConfig<float> config;
		config.pointSize = pointSize->GetValue();
		config.lineWidth = lineWidth->GetValue();
		config.drawVolume = drawVolume->GetValue();
		config.drawCells = drawCells->GetValue();
		config.drawNormal = drawNormal->GetValue();
		return config;
	}

private:
	wxSpinCtrlDouble* pointSize;
	wxSpinCtrlDouble* lineWidth;
	wxCheckBox* drawVolume;
	wxCheckBox* drawCells;
	wxCheckBox* drawNormal;
};

	}
}

#endif