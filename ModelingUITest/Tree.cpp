#include <stdafx.h>

#include "Tree.h"

#include "../Graphics/Light.h"

using namespace Crystal::Graphics;
using namespace Crystal::Modeling;

#include "Resource/unchecked.xpm"
#include "Resource/checked.xpm"


PolygonTree::PolygonTree
(
wxWindow *parent,
const wxPoint& pos,
const wxSize& size,
PolygonProperty* property,
const PolygonBuilderSPtr& builder
)
:
wxTreeCtrl(
parent,
wxNewId(),
pos,
size//,
//wxTR_HAS_BUTTONS|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER
),
property(property),
builder(builder)
{
	SetSize(100, 500);
	Connect(this->GetId(), wxEVT_TREE_ITEM_MENU,			wxTreeEventHandler(PolygonTree::OnMenu));
	Connect(this->GetId(), wxEVT_TREE_ITEM_ACTIVATED,		wxTreeEventHandler(PolygonTree::OnItemActivated));
	Connect(this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK,	wxTreeEventHandler(PolygonTree::OnItemStateClick));

	const wxTreeItemId root = AddRoot("Polygon");

	wxIcon unchecked = wxIcon(unchecked_xpm);
	wxIcon checked = wxIcon(checked_xpm);

	wxImageList *states = new wxImageList(24, 24, true);
	states->Add(unchecked);
	states->Add(checked);

	AssignStateImageList(states);
}

void PolygonTree::build()
{
	map.clear();
	DeleteAllItems();
	const wxTreeItemId root = AddRoot("Polygon");

	for (const PolygonSPtr& g : builder->getPolygons()) {
		const wxTreeItemId id = AppendItem(root, g->getName());
		map[id] = g;
		//SetItemState( id, polygon->isSelected );
	}
}

void PolygonTree::OnItemStateClick(wxTreeEvent& event)
{
	const wxTreeItemId id = event.GetItem();

	if (map.find(id) == map.end()) {
		return;
	}
	const PolygonSPtr& p = map[id];
	property->build( p );
}

void PolygonTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;

	wxMenuItem* add = menu.Append(wxNewId(), "Add");
	wxMenuItem* del = menu.Append(wxNewId(), "Delete");
	wxMenuItem* clear = menu.Append(wxNewId(), "Clear");

	Connect(add->GetId(),	wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(PolygonTree::OnAdd));
	Connect(del->GetId(),	wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(PolygonTree::OnDelete));
	Connect(clear->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(PolygonTree::OnClear));

	PopupMenu(&menu, event.GetPoint());

	event.Skip();
}

PolygonTree::~PolygonTree()
{
}

void PolygonTree::OnAdd(wxMenuEvent&)
{
	const wxString& str = wxGetTextFromUser("Name");
	PolygonSPtr m = builder->build();
	m->setName(str.ToStdString());
	build();
}

void PolygonTree::OnDelete(wxMenuEvent&)
{
	const wxTreeItemId id = GetFocusedItem();
	builder->remove(map[id]);
	Delete(id);
}


void PolygonTree::OnClear(wxMenuEvent&)
{
	builder->clear();
	map.clear();
	DeleteChildren(GetRootItem());
}

void PolygonTree::OnItemActivated(wxTreeEvent& event)
{
	const wxTreeItemId id = event.GetItem();

	if (map.find(id) == map.end()) {
		return;
	}
	const Graphics::PolygonSPtr& p = map[id];
	property->build(p);
}
