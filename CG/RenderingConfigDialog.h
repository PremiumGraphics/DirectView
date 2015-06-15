#ifndef __CRYSTAL_UI_RENDERING_CONFIG_DIALOG_H__
#define __CRYSTAL_UI_RENDERING_CONFIG_DIALOG_H__

#include "stdafx.h"

#include "../Command/MainConfig.h"

namespace Crystal {
	namespace Graphics {

class RenderingConfigDialog : public wxDialog
{
public:
	RenderingConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "RenderingConfig", wxDefaultPosition, wxSize( 500, 500 ) )
	{
		new wxStaticText(this, wxID_ANY, "PointSize", wxPoint(0, 100));
		pointSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "LineWidth", wxPoint(0, 200));
		lineWidth = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		new wxStaticText(this, wxID_ANY, "BoundingBox", wxPoint(0, 300));
		drawBB = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(100, 300) );

		new wxButton( this, wxID_OK, "OK", wxPoint(300,300) );
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));
	}

	void set(const Command::RenderingConfig<float>& config) {
		pointSize->SetValue( config.getPointSize() );
		lineWidth->SetValue( config.getLineWidth() );
		drawBB->SetValue( config.drawBB() );
	}

	Command::RenderingConfig<float> get() {
		const auto p = pointSize->GetValue();
		const auto l = lineWidth->GetValue();
		return Command::RenderingConfig<float>(p, l, drawBB->GetValue());
	}

private:
	wxSpinCtrlDouble* pointSize;
	wxSpinCtrlDouble* lineWidth;
	wxCheckBox* drawBB;
};

template<typename T>
class NormalConfigDialog : public wxDialog
{
public:
	NormalConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "NormalConfig", wxDefaultPosition, wxSize(500, 500))
	{
		//new wxStaticText(this, wxID_ANY, "PointSize", wxPoint(0, 100));
		//pointSize = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100));

		new wxStaticText(this, wxID_ANY, "LineWidth", wxPoint(0, 200));
		lineWidth = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));

		//new wxStaticText(this, wxID_ANY, "BoundingBox", wxPoint(0, 300));
		//drawBB = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));

		new wxStaticText(this, wxID_ANY, "NormalScale", wxPoint(0, 300));
		normalScale = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 300));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));
	}

	void set(const Command::NormalConfig<T>& config) {
		lineWidth->SetValue(config.getLineWidth());
		normalScale->SetValue(config.getNormalScale());
	}

	Command::NormalConfig<T> get() {
		const auto n = normalScale->GetValue();
		const auto l = lineWidth->GetValue();
		return Command::NormalConfig<T>(n, l);
	}

private:
	//wxSpinCtrlDouble* pointSize;
	wxSpinCtrlDouble* lineWidth;
	wxSpinCtrlDouble* normalScale;
};

	}
}

#endif