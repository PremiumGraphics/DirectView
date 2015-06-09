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
		wxDialog(parent, wxID_ANY, "GridConfig", wxDefaultPosition, wxSize( 500, 500 ))
	{
		resx = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxPoint(100,100));
		resx->SetMin(8);
		resx->SetMax(255);

		resy = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
		resy->SetMin(8);
		resy->SetMax(255);

		resz = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));
		resz->SetMin(8);
		resz->SetMax(255);
	}

	void set(const Command::GridConfig& config) {
		resx->SetValue(config.resx);
		resy->SetValue(config.resy);
		resz->SetValue(config.resz);
	}

private:
	wxSpinCtrl* resx;
	wxSpinCtrl* resy;
	wxSpinCtrl* resz;
};
	}

}

#endif