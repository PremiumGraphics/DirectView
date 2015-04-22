#include "stdafx.h"

#include "ParticleTree.h"

using namespace Crystal::CG;

ParticleTree::ParticleTree
(
wxWindow *parent,
const wxPoint& pos,
const wxSize& size
//PolygonProperty* property,
//PolygonBuilder& builder
)
:
wxTreeCtrl(
parent,
wxNewId(),
pos,
size//,
//wxTR_HAS_BUTTONS|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER
)
//property(property),
//builder(builder)
{
	SetSize(100, 500);
	Connect(this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(ParticleTree::OnMenu));
	Connect(this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler(ParticleTree::OnItemActivated));
	Connect(this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK, wxTreeEventHandler(ParticleTree::OnItemStateClick));

	build();
	//wxIcon unchecked = wxIcon(unchecked_xpm);
	//wxIcon checked = wxIcon(checked_xpm);

	//wxImageList *states = new wxImageList(24, 24, true);
	//states->Add(unchecked);
	//states->Add(checked);

	//AssignStateImageList(states);
}

void ParticleTree::build()
{
	//map.clear();
	DeleteAllItems();
	const wxTreeItemId root = AddRoot("Particle");

	/*
	for (Graphics::PolygonSPtr p : builder.getPolygons()) {
		const wxTreeItemId id = AppendItem(root, p->getName());
		map[id] = p.get();
		SetItemState(id, p->isSelected);
	}
	*/
}

void ParticleTree::OnItemStateClick(wxTreeEvent& event)
{
	/*
	const wxTreeItemId id = event.GetItem();

	if (map.find(id) == map.end()) {
		return;
	}
	Graphics::Polygon* p = map[id];
	p->isSelected = !p->isSelected;
	SetItemState(id, p->isSelected);
	property->build(p);
	*/
}

void ParticleTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;

	wxMenuItem* add = menu.Append(wxNewId(), "Add");
	wxMenuItem* del = menu.Append(wxNewId(), "Delete");
	wxMenuItem* clear = menu.Append(wxNewId(), "Clear");

	Connect(add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(ParticleTree::OnAdd));
	Connect(del->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(ParticleTree::OnDelete));
	Connect(clear->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(ParticleTree::OnClear));

	PopupMenu(&menu, event.GetPoint());

	event.Skip();
}

ParticleTree::~ParticleTree()
{
}

void ParticleTree::OnAdd(wxMenuEvent&)
{
	//const wxString& str = wxGetTextFromUser("Name");
	//builder.build();

	//PolygonSPtr m = builder.build();
	//m->setName(str.ToStdString());
	build();
}

void ParticleTree::OnDelete(wxMenuEvent&)
{
	const wxTreeItemId id = GetFocusedItem();
	//builder.remove(map[id]);
	Delete(id);
}


void ParticleTree::OnClear(wxMenuEvent&)
{
	/*
	builder.clear();
	map.clear();
	DeleteChildren(GetRootItem());
	*/
}

void ParticleTree::OnItemActivated(wxTreeEvent& event)
{
	/*
	const wxTreeItemId id = event.GetItem();

	if (map.find(id) == map.end()) {
		return;
	}
	Graphics::Polygon* p = map[id];
	property->build(p);
	*/
}
