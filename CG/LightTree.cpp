#include <stdafx.h>

#include "LightTree.h"

#include "../Graphics/Light.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;

#include <algorithm>

#include "Resource/unchecked.xpm"
#include "Resource/checked.xpm"


LightTree::LightTree
(
	wxWindow *parent,
	const wxPoint& pos,
	const wxSize& size,
	LightProperty* property,
	std::list<Light> lights
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
	lights_( lights )
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

	for( Graphics::Light& l : lights_ ) {
		const wxTreeItemId id = AppendItem( root, l.name );
		SetItemState( id, l.isSelected );
		map[id] = &l;
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
	Light light;
	lights_.push_back( light );
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

