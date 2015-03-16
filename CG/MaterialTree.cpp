#include <stdafx.h>

#include "MaterialTree.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;

#include <algorithm>

MaterialTree::MaterialTree
(
	wxWindow *parent,
	const wxPoint& pos,
	const wxSize& size,
	MaterialProperty* property,
	MaterialSPtrList& materials
	)
	: 
	wxTreeCtrl(
	parent,
	wxNewId(),
	pos,
	size
	),
	property( property ),
	materials( materials )
{
	Connect( this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler( MaterialTree::OnMenu ) );
	Connect( this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( MaterialTree::OnItemActivated ) );

	const wxTreeItemId root = AddRoot("Material");
}

void MaterialTree::build()
{
	map.clear();
	//this->materials = materials;
	DeleteAllItems();
	const wxTreeItemId root = AddRoot( "Material" );

	for( const MaterialSPtr& m : materials ) {
		const wxTreeItemId id = AppendItem( root, m->getName() );
		map[id] = m;
	}
}

void MaterialTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;
	
	wxMenuItem* add = menu.Append( wxNewId(), "Add" );
	wxMenuItem* del = menu.Append( wxNewId(), "Delete" );

	Connect( add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler( MaterialTree::OnAdd ) );
	Connect( del->GetId(), wxEVT_COMMAND_MENU_SELECTED , wxMenuEventHandler( MaterialTree::OnDelete ) );	
	PopupMenu( &menu, event.GetPoint() );

	event.Skip();
}

MaterialTree::~MaterialTree()
{
}

void MaterialTree::OnItemActivated( wxTreeEvent& e )
{
	const wxTreeItemId id = e.GetItem();

	if (map.find(id) == map.end()) {
		return;
	}
	const MaterialSPtr& m = map[id];
	property->setValue(m);
}

void MaterialTree::OnAdd( wxMenuEvent& )
{
	/*
	MaterialSPtr m(new Material());
	m->setName( "test" );
	materials.push_back(m);
	build();
	*/
}

void MaterialTree::OnDelete( wxMenuEvent& )
{
	const wxTreeItemId item = GetFocusedItem();
	if( item == GetRootItem() ) {
		return;
	}

	/*
	const std::string& name = GetItemText( item ).ToStdString();
	Material* m = model->find( name );
	model->remove( m );
	*/
	Delete(item);
}