#ifndef __CRYSTAL_UI_RENDERING_DIALOG_H__
#define __CRYSTAL_UI_RENDERING_DIALOG_H__

#include "stdafx.h"

#include "../Command/MainConfig.h"

namespace Crystal {
	namespace Graphics {

class WireframeConfigDialog : public wxDialog
{
public:
	WireframeConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "RenderingConfig", wxDefaultPosition, wxSize( 500, 500 ) )
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


		new wxButton( this, wxID_OK, "OK", wxPoint(300,300) );
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));
	}

	void set(const Model::RenderingConfig<float>& config) {
		pointSize->SetValue(config.getPointSize());
		lineWidth->SetValue( config.getLineWidth() );
		drawBB->SetValue( config.drawBB() );
		drawPlane->SetValue( config.drawPlane() );
	}

	Model::RenderingConfig<float> get() {
		return Model::RenderingConfig<float>( pointSize->GetValue(), lineWidth->GetValue(), drawBB->GetValue(), drawPlane->GetValue());
	}

private:
	wxSpinCtrlDouble* pointSize;
	wxSpinCtrlDouble* lineWidth;
	wxCheckBox* drawBB;
	wxCheckBox* drawPlane;
};

	}
}

#endif