#ifndef __CRYSTAL_UI_USER_ENTRY_DIALOG_H__
#define __CRYSTAL_UI_USER_ENTRY_DIALOG_H__

#include "wx/dialog.h"

namespace Crystal {
	namespace UI {

		class FloatEntryDialog : public wxDialog
		{
		public:
			FloatEntryDialog(wxWindow* parent, const wxString&  title, const float value);

			void setRange(const float min_, const float max_);

			float getValue() const { return ctrl->GetValue(); }

		private:
			wxSpinCtrlDouble* ctrl;
		};
	}
}

#endif