#ifndef __CRYSTAL_UI_METABALL_DIALOG_H__
#define __CRYSTAL_UI_METABALL_DIALOG_H__

#include "wx/dialog.h"
#include "wx/spinctrl.h"

namespace Crystal {
	namespace UI {

class MetaballDialog : public wxDialog
{
public:
	MetaballDialog(wxWindow* parent) :
		wxDialog( parent, wxID_ANY, "MetaballConfig", wxDefaultPosition, wxSize( 700, 600))
	{
		new wxStaticText(this, wxID_ANY, "CenterX", wxPoint(0, 100));
		posx = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100,100) );
		posx->SetRange(-10000, 10000);

		new wxStaticText(this, wxID_ANY, "CenterY", wxPoint(0, 200));
		posy = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100,200) );
		posy->SetRange(-10000, 10000);

		new wxStaticText(this, wxID_ANY, "CenterZ", wxPoint(0, 300));
		posz = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100,300) );
		posz->SetRange(-10000, 10000);

		new wxStaticText(this, wxID_ANY, "Radius", wxPoint(0, 400));
		radius = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100,400));

		new wxStaticText(this, wxID_ANY, "Charge", wxPoint(0, 500));
		charge = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 500));
		charge->SetRange(-100, 100);

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 300));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));

	}

	void set(const Model::ParticleConfig<float>& config) {
		const auto& center = config.getCenter();
		posx->SetValue(center.getX());
		posy->SetValue(center.getY());
		posz->SetValue(center.getZ());
		radius->SetValue( config.getRadius() );
		charge->SetValue( config.getCharge() );
	}

	Model::ParticleConfig<float> get() const {
		const auto x = posx->GetValue();
		const auto y = posy->GetValue();
		const auto z = posz->GetValue();
		const Math::Vector3d<float> center(x, y, z);
		return Model::ParticleConfig<float>(center, radius->GetValue(), charge->GetValue());
	}

private:
	wxSpinCtrlDouble* posx;
	wxSpinCtrlDouble* posy;
	wxSpinCtrlDouble* posz;
	wxSpinCtrlDouble* radius;
	wxSpinCtrlDouble* charge;
};

	}
}

#endif