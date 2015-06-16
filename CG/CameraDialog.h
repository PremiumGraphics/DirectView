#ifndef __CRYSTAL_UI_CAMERA_DIALOG_H__
#define __CRYSTAL_UI_CAMERA_DIALOG_H__

#include <wx/dialog.h>
#include <wx/spinctrl.h>

namespace Crystal {
	namespace UI {

class CameraDialog : public wxDialog
{
public:
	explicit CameraDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "Camera", wxDefaultPosition, wxSize(500,500))
	{
		posx = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100, 100) );
		posy = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100, 200) );
		posz = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint(100, 300) );

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 300));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));
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