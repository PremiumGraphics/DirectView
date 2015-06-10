#ifndef __CRYSTAL_UI_RENDERING_CONFIG_DIALOG_H__
#define __CRYSTAL_UI_RENDERING_CONFIG_DIALOG_H__

#include "stdafx.h"

namespace Crystal {
	namespace Graphics {

class RenderingConfigDialog : public wxDialog
{
public:
	RenderingConfigDialog(wxWindow* parent) :
		wxDialog(parent, wxID_ANY, "RenderingConfig", wxDefaultPosition, wxSize( 500, 500 ) )
	{
		new wxButton( this, wxID_OK, "OK", wxPoint(300,300) );
	}

private:
};
	}
}

#endif