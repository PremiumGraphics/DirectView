#ifndef __CRYSTAL_APP_POLYGON_TREE_H__
#define __CRYSTAL_APP_POLYGON_TREE_H__

#include <vector>
#include <string>
#include <list>

#include "Model.h"

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
		std::list<Polygon> polygons
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

	std::list<Polygon> polygons;
};

	}
}

#endif