#ifndef __CRYSTAL_UI_USER_ENTRY_DIALOG_H__
#define __CRYSTAL_UI_USER_ENTRY_DIALOG_H__

#include "wx/dialog.h"

namespace Crystal {
	namespace UI {

		class FloatEntryDialog : public wxDialog
		{
		public:
			FloatEntryDialog(wxWindow* parent, const wxString&  title, const float value) :
				wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 200))
			{
				new wxStaticText(this, wxID_ANY, "Input", wxPoint(0, 50));
				ctrl = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(50, 50));
				ctrl->SetValue(value);

				new wxButton(this, wxID_OK, "OK", wxPoint(0, 100));
				new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(100, 100));
			}

			void setRange(const float min_, const float max_) {
				ctrl->SetRange(min_, max_);

			}

			float getValue() const { return ctrl->GetValue(); }

		private:
			wxSpinCtrlDouble* ctrl;
		};
	}
}

#endif