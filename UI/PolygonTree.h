#ifndef __CRYSTAL_UI_POLYGON_MODELING_TREE_H__
#define __CRYSTAL_UI_POLYGON_MODELING_TREE_H__

#include <vector>
#include <string>
#include <map>
#include <list>

#include "PropertyDialog.h"


#include "../Graphics/Material.h"
#include "../IO/PolygonFactory.h"


#include <memory>

namespace Crystal {
	namespace Modeling {


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
		const Graphics::PolygonBuilderSPtr& builder
		);

	~PolygonTree();

	void build();

	void OnItemActivated(wxTreeEvent& event);

private:
	void OnItemStateClick(wxTreeEvent& event);

	void OnMenu(wxTreeEvent& event);

	void OnAdd(wxMenuEvent&);

	void OnDelete(wxMenuEvent&);

	void OnClear(wxMenuEvent&);

	PolygonProperty* property;

	Graphics::PolygonBuilderSPtr builder;

	std::map< wxTreeItemId, Graphics::PolygonSPtr > map;
};

	}
}


#endif