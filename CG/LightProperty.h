#ifndef __CRYSTAL_APP_LIGHT_PROPERTY_H__
#define __CRYSTAL_APP_LIGHT_PROPERTY_H__

#include "../Graphics/Light.h"

namespace Crystal {
	namespace CG {

class LightProperty : public wxPropertyGrid {
public:
	LightProperty(wxWindow* parent, const wxSize& size);

	void setValue( Graphics::Light* light );

private:
	Graphics::Light* light;

	void OnChange( wxPropertyGridEvent& event );
};

	}
}

#endif