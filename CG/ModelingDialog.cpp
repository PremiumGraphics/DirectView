#include "stdafx.h"
#include "ModelingDialog.h"

using namespace Crystal::CG;

TriangleConfigDialog::TriangleConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "QuadConfig", wxDefaultPosition, wxSize(500, 500))
{
	new wxStaticText(this, wxID_ANY, "X Size", wxPoint(0, 100));
	xSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

	new wxStaticText(this, wxID_ANY, "Y Size", wxPoint(0, 200));
	ySize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

	new wxButton(this, wxID_OK, "OK", wxPoint(300, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 200));
}

void TriangleConfigDialog::setConfig(const Config& config) {
	xSize->SetValue(config.xSize);
	ySize->SetValue(config.ySize);
}

TriangleConfigDialog::Config TriangleConfigDialog::getConfig() const {
	Config config;
	config.xSize = xSize->GetValue();
	config.ySize = ySize->GetValue();
	return config;
}
