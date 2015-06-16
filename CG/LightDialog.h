#ifndef __CRYSTAL_UI_LIGHT_DIALOG_H__
#define __CRYSTAL_UI_LIGHT_DIALOG_H__

#include <wx/dialog.h>
#include <wx/spinctrl.h>

namespace Crystal {
	namespace UI{

class AmbientLightDialog : public wxDialog
{
public:
	AmbientLightDialog(wxWindow* parent) :
		wxDialog( parent, wxID_ANY, "AmbientLight", wxDefaultPosition, wxSize( 500, 500 ) )
	{
		color = new wxColourPickerCtrl(this, wxID_ANY, wxColour(), wxPoint(100, 100 ) );
		//wxSpinCtrlDouble* pos;

		new wxButton(this, wxID_OK, "OK", wxPoint(300, 300));
		new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(300, 400));
	}

private:
	wxColourPickerCtrl* color;

};

class DirectionalLightDialog : public wxDialog
{
public:
	DirectionalLightDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "DirectionalLight")
	{}
};
	}
}

#endif