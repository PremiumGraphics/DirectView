#include <stdafx.h>
#include "UserEntryDialog.h"

using namespace Crystal::UI;

FloatEntryDialog::FloatEntryDialog(wxWindow* parent, const wxString&  title, const float value) :
wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 200))
{
	new wxStaticText(this,wxID_ANY, "Input", wxPoint( 0, 50));
	ctrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxPoint( 50, 50 ) );
	ctrl->SetValue(value);

	new wxButton(this, wxID_OK, "OK", wxPoint(0, 100));
	new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(100, 100));

}

void FloatEntryDialog::setRange(const float _min, const float _max)
{
	ctrl->SetRange(_min, _max);
}