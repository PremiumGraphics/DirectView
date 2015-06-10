#ifndef __CRYSTAL_UI_GRID_CONFIG_DIALOG_H__
#define __CRYSTAL_UI_GRID_CONFIG_DIALOG_H__

#include "wx/dialog.h"
#include "wx/spinctrl.h"

#include "../Command/GridConfig.h"

namespace Crystal {
	namespace UI {

class GridConfigDialog : public wxDialog 
{
public:
	GridConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "GridConfig", wxDefaultPosition, wxSize( 700, 500 ))
	{
		resx = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxPoint(100,100));
		resx->SetRange( Command::GridConfig::MINX, Command::GridConfig::MAXX);

		resy = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
		resy->SetRange( Command::GridConfig::MINY, Command::GridConfig::MAXY);

		resz = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));
		resz->SetRange( Command::GridConfig::MINZ, Command::GridConfig::MAXZ);

		originx = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 100));
		originy = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 200));
		originz = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 300));

		originx->SetRange(-10000, 10000);
		originy->SetRange(-10000, 10000);
		originz->SetRange(-10000, 10000);

		lengthx = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(500, 100));
		lengthy = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(500, 200));
		lengthz = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(500, 300));

		lengthx->SetRange(-10000, 10000);
		lengthy->SetRange(-10000, 10000);
		lengthz->SetRange(-10000, 10000);

		new wxButton(this, wxID_OK, "OK", wxPoint( 100, 400));
	}

	void set(const Command::GridConfig& config) {
		resx->SetValue(config.getResx());
		resy->SetValue(config.getResy());
		resz->SetValue(config.getResz());

		const auto& space = config.getSpace();
		originx->SetValue( space.getStart().getX() );
		originy->SetValue( space.getStart().getY() );
		originz->SetValue( space.getStart().getZ());

		const auto& length = space.getLengths();
		lengthx->SetValue(length.getX());
		lengthy->SetValue(length.getY());
		lengthz->SetValue(length.getZ());
	}

	Command::GridConfig get() const {
		const auto x = resx->GetValue();
		const auto y = resy->GetValue();
		const auto z = resz->GetValue();
		return Command::GridConfig(x, y, z, getSpace());
	}

	//void OnOk() 

private:
	wxSpinCtrl* resx;
	wxSpinCtrl* resy;
	wxSpinCtrl* resz;

	wxSpinCtrlDouble* originx;
	wxSpinCtrlDouble* originy;
	wxSpinCtrlDouble* originz;

	wxSpinCtrlDouble* lengthx;
	wxSpinCtrlDouble* lengthy;
	wxSpinCtrlDouble* lengthz;


	Math::Space3d<float> getSpace() const {
		Math::Vector3d<float> origin(
			originx->GetValue(),
			originy->GetValue(),
			originz->GetValue()
			);

		Math::Vector3d<float> length(
			lengthx->GetValue(),
			lengthy->GetValue(),
			lengthz->GetValue()
		);
		return Math::Space3d<float>(origin, length);
	}
};
	}

}

#endif