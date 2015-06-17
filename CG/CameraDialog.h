#ifndef __CRYSTAL_UI_CAMERA_DIALOG_H__
#define __CRYSTAL_UI_CAMERA_DIALOG_H__

#include <wx/dialog.h>
#include <wx/spinctrl.h>

#include "../Command/CameraModel.h"

namespace Crystal {
	namespace UI {

class CameraDialog : public wxDialog
{
public:
	explicit CameraDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "Camera", wxDefaultPosition, wxSize(500,500))
	{
		new wxStaticText(this, wxID_ANY, "PosX", wxPoint(0, 100));
		posx = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100, 100) );
		new wxStaticText(this, wxID_ANY, "PosY", wxPoint(0, 200));
		posy = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100, 200) );
		new wxStaticText(this, wxID_ANY, "PosZ", wxPoint(0, 300));
		posz = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100, 300) );

		//const int id = GetN
		new wxButton(this, wxID_ANY, "Reset", wxPoint( 500, 0) );

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 300));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));
	}

	void set(const Model::CameraObject<float>& camera) {
		const auto& c = camera.getCamera();
		posx->SetValue(c->getPos().getX());
		posy->SetValue(c->getPos().getY());
		posz->SetValue(c->getPos().getZ());
	}

private:
	wxSpinCtrlDouble* posx;
	wxSpinCtrlDouble* posy;
	wxSpinCtrlDouble* posz;
	wxSpinCtrlDouble* left;
	wxSpinCtrlDouble* right;
	wxSpinCtrlDouble* near_;
	wxSpinCtrlDouble* far_;
};
	}
}

#endif