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
	MaterialProperty* property
	)
	: 
	wxTreeCtrl(
	parent,
	wxNewId(),
	pos,
	size
	),
	property( property )
{
	Connect( this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler( MaterialTree::OnMenu ) );
	Connect( this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( MaterialTree::OnItemActivated ) );

	const wxTreeItemId root = AddRoot("Material");
}

void MaterialTree::build( std::unique_ptr< std::list<Material*> >& materials)
{
	//this->materials = materials;
	DeleteAllItems();
	const wxTreeItemId root = AddRoot( "Material" );

	for( Material* m : *materials ) {
		const wxTreeItemId id = AppendItem( root, m->name );
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
	const std::string& name = GetItemText( id ).ToStdString();

	/*
	for( Material* m : model->getMaterials() ) {
		if( m->name == name ) {
			property->setValue( m );
		}
	}
	*/
}

void MaterialTree::OnAdd( wxMenuEvent& )
{
	const wxTreeItemId root = GetRootItem();
	//const wxTreeItemId id = AppendItem( root, "Item" );
	std::string name = "MaterialX";
	AppendItem( root, name );

	//Material* m = new Material();
	materials->push_back(new Material());
	//m->name = name;
	//model->push_back( m );
	//model->push_back( m );
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