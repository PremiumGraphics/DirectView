#ifndef __CRYSTAL_UI_VOLUME_DIALOG_H__
#define __CRYSTAL_UI_VOLUME_DIALOG_H__

#include "wx/dialog.h"
#include "wx/spinctrl.h"

namespace Crystal {
	namespace UI {

class VolumeDialog : public wxDialog 
{
private:
	enum LIMIT{
		MINX = 8,
		MINY = 8,
		MINZ = 8,
		MAXX = 255,
		MAXY = 255,
		MAXZ = 255,
	};


public:
	VolumeDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "GridConfig", wxDefaultPosition, wxSize( 700, 500 ))
	{
		new wxStaticText(this, wxID_ANY, "Resolution", wxPoint(100, 0));

		new wxStaticText(this, wxID_ANY, "X", wxPoint(0, 100));
		resx = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxPoint(100,100));
		resx->SetRange( LIMIT::MINX, LIMIT::MAXX);

		new wxStaticText(this, wxID_ANY, "Y", wxPoint(0, 200));
		resy = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200));
		resy->SetRange( LIMIT::MINY, LIMIT::MAXY);

		new wxStaticText(this, wxID_ANY, "Z", wxPoint(0, 300));
		resz = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 300));
		resz->SetRange( LIMIT::MINZ, LIMIT::MAXZ);

		new wxStaticText(this, wxID_ANY, "Origin", wxPoint(300, 0));
		originx = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 100));
		originy = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 200));
		originz = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 300));

		originx->SetRange(-10000, 10000);
		originy->SetRange(-10000, 10000);
		originz->SetRange(-10000, 10000);

		new wxStaticText(this, wxID_ANY, "Size", wxPoint(500, 0));
		lengthx = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(500, 100));
		lengthy = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(500, 200));
		lengthz = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(500, 300));

		lengthx->SetRange(-10000, 10000);
		lengthy->SetRange(-10000, 10000);
		lengthz->SetRange(-10000, 10000);

		new wxButton(this, wxID_OK, "OK", wxPoint( 400, 400));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(500, 400));
	}

	void set(const Model::VolumeConfig<float>& config) {
		resx->SetValue( config.getResx() );
		resy->SetValue( config.getResy() );
		resz->SetValue( config.getResz() );

		const auto& space = config.getSpace();
		originx->SetValue( space.getStart().getX() );
		originy->SetValue( space.getStart().getY() );
		originz->SetValue( space.getStart().getZ());

		const auto& length = space.getLengths();
		lengthx->SetValue(length.getX());
		lengthy->SetValue(length.getY());
		lengthz->SetValue(length.getZ());
	}

	Model::VolumeConfig<float> get() const {
		const auto x = resx->GetValue();
		const auto y = resy->GetValue();
		const auto z = resz->GetValue();
		return Model::VolumeConfig<float>(x, y, z, getSpace());
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