#include <stdafx.h>

#include "PolygonTree.h"
#include "PolygonProperty.h"

#include "../Graphics/Material.h"
#include "MaterialTree.h"


#include "../Math/Box.h"

#include "Resource/unchecked.xpm"
#include "Resource/checked.xpm"
#include <algorithm>


using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;


PolygonTree::PolygonTree
(
	wxWindow *parent,
	const wxPoint& pos,
	const wxSize& size,
	PolygonProperty* property,
	PolygonSPtrList& polygons,
	MaterialList& materials
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
	polygons( polygons ),
	materials( materials )
{
	SetSize( 100, 500 );
	Connect( this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler( PolygonTree::onMenu ) );
	Connect( this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( PolygonTree::OnItemActivated ) );
	Connect( this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK, wxTreeEventHandler( PolygonTree::OnItemStateClick ) );

	const wxTreeItemId root = AddRoot( "Polygon" );

    wxIcon unchecked = wxIcon(unchecked_xpm);
	wxIcon checked = wxIcon(checked_xpm );

	wxImageList *states = new wxImageList(24, 24, true);
	states->Add( unchecked );
	states->Add( checked );

    AssignStateImageList(states);
}

void PolygonTree::build()
{
	map.clear();
	DeleteAllItems();
	const wxTreeItemId root = AddRoot( "Polygon" );

	this->polygons = polygons;

	for (const PolygonSPtr& g:  polygons) {
		const wxTreeItemId id = AppendItem( root, g->getName() );
		map[id] = g;
		//SetItemState( id, polygon->isSelected );
	}
}

void PolygonTree::OnItemStateClick(wxTreeEvent& event)
{
    // toggle item state
	const wxTreeItemId itemId = event.GetItem();
	const std::string& name = GetItemText( itemId ).ToStdString();

	/*
	Crystal::Graphics::Polygon* p = model->find( name );
	p->isSelected = !p->isSelected;
	SetItemState( itemId, p->isSelected );
	*/
}

void PolygonTree::onMenu(wxTreeEvent& event)
{
	wxMenu menu;
	
	wxMenuItem* add = menu.Append( wxNewId(), "Add" );
	wxMenuItem* del = menu.Append( wxNewId(), "Delete" );

	Connect( add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler( PolygonTree::onAdd ) );
	Connect( del->GetId(), wxEVT_COMMAND_MENU_SELECTED , wxMenuEventHandler( PolygonTree::OnDelete ) );	
	PopupMenu( &menu, event.GetPoint() );

	event.Skip();
}

PolygonTree::~PolygonTree()
{
}

void PolygonTree::onAdd( wxMenuEvent& )
{
}

void PolygonTree::OnDelete( wxMenuEvent& )
{
	const wxTreeItemId item = GetFocusedItem();

	const std::string& name = GetItemText( item ).ToStdString();

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

