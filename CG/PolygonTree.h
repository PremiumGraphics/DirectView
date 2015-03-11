#ifndef __CRYSTAL_APP_POLYGON_TREE_H__
#define __CRYSTAL_APP_POLYGON_TREE_H__

#include <vector>
#include <string>
#include <list>
#include <map>

#include "../Graphics/Material.h"
#include "../Graphics/PolygonGroup.h"
#include "../IO/PolygonFactory.h"

namespace Crystal {
	namespace CG {
		class PolygonProperty;
		
class PolygonTree : public wxTreeCtrl
{
public:
	PolygonTree
		(
		wxWindow *parent,
		const wxPoint& pos,
		const wxSize& size,
		PolygonProperty* property,
		Graphics::PolygonGroupList& polygons,
		Graphics::MaterialList& materials
		);

	~PolygonTree();

	void build();

	void OnItemActivated(wxTreeEvent& event);

private:
	void OnItemStateClick(wxTreeEvent& event);

	void onMenu(wxTreeEvent& event);

	void onAdd( wxMenuEvent& );

	void OnDelete( wxMenuEvent& );

	PolygonProperty* property;

	Graphics::PolygonGroupList& polygons;

	Graphics::MaterialList& materials;

	std::map< wxTreeItemId, Graphics::PolygonSPtr > map;
};

	}
}

#endif