#ifndef __CRYSTAL_APP_MATERIAL_PROPERTY_H__
#define __CRYSTAL_APP_MATERIAL_PROPERTY_H__

#include "../Graphics/Material.h"

namespace Crystal {
	namespace CG {


class MaterialProperty : public wxPropertyGrid {
public:
	MaterialProperty(wxWindow* parent, const wxSize& size );

	void setValue( const Graphics::MaterialSPtr& material );

	void OnChange( wxPropertyGridEvent& event );

	void OnDoubleClick( wxPropertyGridEvent& event );

private:
	Graphics::MaterialSPtr m;
	//wxColourProperty* diffuse;

	wxString getImageFile();

};

	}
}

#endif