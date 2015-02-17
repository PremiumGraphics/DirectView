#ifndef __CRYSTAL_APP_MATERIAL_TREE_H__
#define __CRYSTAL_APP_MATERIAL_TREE_H__

#include <vector>
#include <string>

#include "../Graphics/Material.h"

#include "MaterialProperty.h"

namespace Crystal {
	namespace CG {
		
class MaterialTree : public wxTreeCtrl
{
public:
	MaterialTree
		(
		wxWindow *parent,
		const wxPoint& pos,
		const wxSize& size,
		MaterialProperty* property
		);

	~MaterialTree();

	void build();

private:
	void onMenu(wxTreeEvent& event);

	void OnAdd( wxMenuEvent& );

	void OnDelete( wxMenuEvent& );

	void OnItemActivated(wxTreeEvent& event);


	MaterialProperty* property;
};

	}
}

#endif