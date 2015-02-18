#ifndef __CRYSTAL_APP_MATERIAL_TREE_H__
#define __CRYSTAL_APP_MATERIAL_TREE_H__

#include <vector>
#include <string>
#include <map>
#include <memory>

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

	void build( std::unique_ptr< std::list<Graphics::Material*> >& materials);

private:
	void OnMenu(wxTreeEvent& event);

	void OnAdd( wxMenuEvent& );

	void OnDelete( wxMenuEvent& );

	void OnItemActivated(wxTreeEvent& event);

	std::unique_ptr< std::list< Graphics::Material* > > materials;

	MaterialProperty* property;

	std::map< wxTreeItemId, Graphics::Material* > map;
};

	}
}

#endif