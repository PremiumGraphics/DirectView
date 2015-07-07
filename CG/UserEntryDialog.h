#ifndef __CRYSTAL_UI_USER_ENTRY_DIALOG_H__
#define __CRYSTAL_UI_USER_ENTRY_DIALOG_H__

#include "wx/dialog.h"

namespace Crystal {
	namespace UI {

		class FloatEntryDialog : public wxDialog
		{
		public:
			FloatEntryDialog(wxWindow* parent, const wxString&  title);

			float getValue() const { return ctrl->GetValue(); }

		private:
			wxSpinCtrlDouble* ctrl;
		};
	}
}

#endif