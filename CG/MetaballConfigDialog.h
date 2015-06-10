#ifndef __CRYSTAL_UI_METABALL_CONFIG_DIALOG_H__
#define __CRYSTAL_UI_METABALL_CONFIG_DIALOG_H__

#include "wx/dialog.h"
#include "wx/spinctrl.h"

#include "../Command/MetaballConfig.h"

namespace Crystal {
	namespace UI {

class MetaballConfigDialog : public wxDialog
{
public:
	MetaballConfigDialog(wxWindow* parent) :
		wxDialog( parent, wxID_ANY, "MetaballConfig", wxDefaultPosition, wxSize( 700, 500))
	{
		posx = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100,100) );
		posx->SetRange(-10000, 10000);
		posy = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100,200) );
		posy->SetRange(-10000, 10000);
		posz = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100,300) );
		posz->SetRange(-10000, 10000);
		radius = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100,400));
	}

	void set(const Command::MetaballConfig& config) {
		const auto center = config.getCenter();
		posx->SetValue(center.getX());
		posy->SetValue(center.getY());
		posz->SetValue(center.getZ());
		radius->SetValue(config.getRadius());
	}

	Command::MetaballConfig get() const {
		const auto x = posx->GetValue();
		const auto y = posy->GetValue();
		const auto z = posz->GetValue();
		const Math::Vector3d<float> center(x, y, z);
		return Command::MetaballConfig(center, radius->GetValue());
	}

private:
	wxSpinCtrlDouble* posx;
	wxSpinCtrlDouble* posy;
	wxSpinCtrlDouble* posz;
	wxSpinCtrlDouble* radius;
};

	}
}

#endif