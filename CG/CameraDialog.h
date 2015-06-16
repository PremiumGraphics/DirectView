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
		;
	}

private:
	wxSpinCtrlDouble* posx;
	wxSpinCtrlDouble* posy;
	wxSpinCtrlDouble* posz;
};
	}
}

#endif