#include <stdafx.h>
#include "UserEntryDialog.h"

using namespace Crystal::UI;

FloatEntryDialog::FloatEntryDialog(wxWindow* parent, const wxString&  title) :
wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(200, 200))
{
	new wxStaticText(this,wxID_ANY, "Input", wxPoint( 0, 50));
	ctrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint( 50, 50 ) );

	new wxButton(this, wxID_OK, "OK", wxPoint(400, 400));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(500, 400));

}
