#include <stdafx.h>

#include "Tree.h"

#include "../Graphics/Light.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;

#include "Resource/unchecked.xpm"
#include "Resource/checked.xpm"


LightTree::LightTree
(
	wxWindow *parent,
	const wxPoint& pos,
	const wxSize& size,
	LightProperty* property,
	LightBuilder& builder
	)
	: 
	wxTreeCtrl(
	parent,
	wxNewId(),
	pos,
	size//,
	//wxTR_HAS_BUTTONS|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER
	),
	property( property ),
	builder( builder )
{
	//SetSize( 100, 500 );
	Connect( this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler( LightTree::OnMenu ) );
	Connect( this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( LightTree::OnItemActivated ) );
	Connect( this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK, wxTreeEventHandler( LightTree::OnItemStateClick ) );

	//const wxTreeItemId root = AddRoot( "Material" );

    wxIcon unchecked = wxIcon(unchecked_xpm);
	wxIcon checked = wxIcon(checked_xpm );

	wxImageList *states = new wxImageList(24, 24, true);
	states->Add( unchecked );
	states->Add( checked );

    AssignStateImageList(states);

	build();
}

void LightTree::build()
{
	DeleteAllItems();
	map.clear();

	const wxTreeItemId root = AddRoot( "Light" );

	for( const LightSPtr& l : builder.getLights() ) {
		const wxTreeItemId id = AppendItem( root, l->name );
		//SetItemState( id, l.isSelected );
		map[id] = l;
	}
}

void LightTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;
	
	wxMenuItem* add = menu.Append( wxNewId(), "Add" );
	wxMenuItem* del = menu.Append( wxNewId(), "Delete" );

	Connect( add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler( LightTree::OnAdd ) );
	Connect( del->GetId(), wxEVT_COMMAND_MENU_SELECTED , wxMenuEventHandler( LightTree::OnDelete ) );	
	PopupMenu( &menu, event.GetPoint() );

	event.Skip();
}

void LightTree::OnAdd(wxMenuEvent&)
{
	//LightSPtr light( new Light() );
	//lights_.push_back( light );
	builder.
	build();
}

LightTree::~LightTree()
{
}

void LightTree::OnItemActivated( wxTreeEvent& e )
{
	const wxTreeItemId id = e.GetItem();
	const std::string& name = GetItemText( id ).ToStdString();

	property->setValue( map[id] );
}


MaterialTree::MaterialTree
(
wxWindow *parent,
const wxPoint& pos,
const wxSize& size,
MaterialProperty* property,
MaterialBuilderSPtr& builder
)
:
wxTreeCtrl(
parent,
wxNewId(),
pos,
size
),
property(property),
builder(builder)
{
	Connect(this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MaterialTree::OnMenu));
	Connect(this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler(MaterialTree::OnItemActivated));

	const wxTreeItemId root = AddRoot("Material");
}

void MaterialTree::build()
{
	map.clear();
	//this->materials = materials;
	DeleteAllItems();
	const wxTreeItemId root = AddRoot("Material");

	for (const MaterialSPtr& m : builder->getMaterials()) {
		const wxTreeItemId id = AppendItem(root, m->getName());
		map[id] = m;
	}
}

void MaterialTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;

	wxMenuItem* add = menu.Append(wxNewId(), "Add");
	wxMenuItem* del = menu.Append(wxNewId(), "Delete");

	Connect(add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(MaterialTree::OnAdd));
	Connect(del->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(MaterialTree::OnDelete));
	PopupMenu(&menu, event.GetPoint());

	event.Skip();
}

MaterialTree::~MaterialTree()
{
}

void MaterialTree::OnItemActivated(wxTreeEvent& e)
{
	const wxTreeItemId id = e.GetItem();

	if (map.find(id) == map.end()) {
		return;
	}
	const MaterialSPtr& m = map[id];
	property->setValue(m);
}

void MaterialTree::OnAdd(wxMenuEvent&)
{
	builder->build();
	build();
}

void MaterialTree::OnDelete(wxMenuEvent&)
{
	const wxTreeItemId item = GetFocusedItem();
	if (item == GetRootItem()) {
		return;
	}

	/*
	const std::string& name = GetItemText( item ).ToStdString();
	Material* m = model->find( name );
	model->remove( m );
	*/
	Delete(item);
}


PolygonTree::PolygonTree
(
wxWindow *parent,
const wxPoint& pos,
const wxSize& size,
PolygonProperty* property,
PolygonBuilder& builder
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
	Connect(this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(PolygonTree::OnMenu));
	Connect(this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler(PolygonTree::OnItemActivated));
	Connect(this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK, wxTreeEventHandler(PolygonTree::OnItemStateClick));

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

	for (const PolygonSPtr& g : builder.getPolygons()) {
		const wxTreeItemId id = AppendItem(root, g->getName());
		map[id] = g;
		//SetItemState( id, polygon->isSelected );
	}
}

void PolygonTree::OnItemStateClick(wxTreeEvent& event)
{
	// toggle item state
	const wxTreeItemId itemId = event.GetItem();
	const std::string& name = GetItemText(itemId).ToStdString();

	/*
	Crystal::Graphics::Polygon* p = model->find( name );
	p->isSelected = !p->isSelected;
	SetItemState( itemId, p->isSelected );
	*/
}

void PolygonTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;

	wxMenuItem* add = menu.Append(wxNewId(), "Add");
	wxMenuItem* del = menu.Append(wxNewId(), "Delete");

	Connect(add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(PolygonTree::OnAdd));
	Connect(del->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(PolygonTree::OnDelete));
	PopupMenu(&menu, event.GetPoint());

	event.Skip();
}

PolygonTree::~PolygonTree()
{
}

void PolygonTree::OnAdd(wxMenuEvent&)
{
}

void PolygonTree::OnDelete(wxMenuEvent&)
{
	const wxTreeItemId item = GetFocusedItem();

	const std::string& name = GetItemText(item).ToStdString();

	/*
	Graphics::Polygon* p = model->find( name );// property->build( polygon );
	if( p == nullptr ) {
	return;
	}
	model->remove( p );
	*/
	Delete(item);
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

