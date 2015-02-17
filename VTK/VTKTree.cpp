#include <stdafx.h>

#include "View.h"

#include "VTKTree.h"
#include "VTKPropertyGrid.h"
#include "ColorMapPanel.h"

#include "Resource/unchecked.xpm"
#include "Resource/checked.xpm"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::App;
using namespace Crystal::IO;

#include <algorithm>

VTKTree::VTKTree
(
	wxWindow *parent,
	View* view,
	const wxPoint& pos,
	const wxSize& size,
	VTKObjectFactory* factory,
	VTKPropertyGrid* propertyGrid
	)
	: 
	wxTreeCtrl(
	parent,
	wxNewId(),
	pos,
	size
	),
	factory( factory ),
	propertyGrid( propertyGrid ),
	view( view )
{
	Connect( this->GetId(), wxEVT_TREE_ITEM_MENU, wxTreeEventHandler( VTKTree::OnMenu ) );
	Connect( this->GetId(), wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( VTKTree::OnItemActivated ) );
	Connect( this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK, wxTreeEventHandler( VTKTree::OnItemStateClick ) );

    wxIcon unchecked = wxIcon(unchecked_xpm);
	wxIcon checked = wxIcon(checked_xpm );

	wxImageList *states = new wxImageList(24, 24, true);
	states->Add( unchecked );
	states->Add( checked );

    AssignStateImageList(states);

	//build();
}

void VTKTree::build()
{
	objectMap.clear();
	attributeMap.clear();
	colorMapMap.clear();


	DeleteAllItems();

	const wxTreeItemId root = AddRoot( "VTK" );

	for( VTKObject* object : factory->getObjects() ) {
		const wxTreeItemId& objectId = AppendItem( root, object->getName() );
		objectMap[ objectId ] = object;
		SetItemState( objectId, object->isSelected() );

		const wxTreeItemId& nodeId = AppendItem( objectId, "節点要素" );
		for( IO::VTKAttributes* attr : object->getNodeAttributes() ) {
			const wxTreeItemId id = AppendItem( nodeId, attr->getName() );
			attributeMap[ id ] = attr;
			SetItemState( id, attr->isSelected() );
		}

		const wxTreeItemId& cellId = AppendItem( objectId, "セル要素" );
		for( IO::VTKAttributes* attr : object->getCellAttributes() ) {
			const wxTreeItemId id = AppendItem( cellId, attr->getName() );
			attributeMap[ id ] = attr;
			SetItemState( id, attr->isSelected() );
		}

		const wxTreeItemId& colorMapId = AppendItem( objectId, "カラーマップ" );
		for( Graphics::ColorRGBAMap<float>* map : object->getColorMaps() ) {
			const wxTreeItemId id = AppendItem( colorMapId, map->getName() );
			colorMapMap[ id ] = map;
			//attributeMap[ id ] = attr;
		}

	} 
}

void VTKTree::OnMenu(wxTreeEvent& event)
{
	const wxTreeItemId id = GetFocusedItem();

	/*
	if( objectMap.find(id) != objectMap.end() ) {
		wxMenu menu;
		wxMenuItem* del = menu.Append( wxNewId(), "削除" );
		Connect( del->GetId(), wxEVT_COMMAND_MENU_SELECTED , wxMenuEventHandler( VTKTree::OnDelete ) );	
		PopupMenu( &menu, event.GetPoint() );
	}
	else */if( GetItemText( id ) == "カラーマップ" ) {
		wxMenu menu;
	
		wxMenuItem* add = menu.Append( wxNewId(), "追加" );

		Connect( add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler( VTKTree::OnAdd ) );
		PopupMenu( &menu, event.GetPoint() );
	}
	else if( colorMapMap.find(id) != colorMapMap.end() ) {
		wxMenu menu;
	
		wxMenuItem* add = menu.Append( wxNewId(), "追加" );
		wxMenuItem* del = menu.Append( wxNewId(), "削除" );

		Connect( add->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler( VTKTree::OnAdd ) );
		Connect( del->GetId(), wxEVT_COMMAND_MENU_SELECTED , wxMenuEventHandler( VTKTree::OnDelete ) );	
		PopupMenu( &menu, event.GetPoint() );
	}

	event.Skip();
}

VTKTree::~VTKTree()
{
}


void VTKTree::OnAdd( wxMenuEvent& )
{
	const wxTreeItemId id = GetFocusedItem();

	if( colorMapMap.find(id) != colorMapMap.end() ) {
		const wxTreeItemId colorMapId = GetItemParent( id );
		const wxTreeItemId objectId = GetItemParent( colorMapId );
		VTKObject* object = objectMap[objectId];
		ColorRGBAMap<float>* map = object->createDefaultColorMap();
		const wxString& name = wxGetTextFromUser("カラーマップ名");
		map->setName( name.ToStdString() );
		const wxTreeItemId newId = AppendItem( colorMapId, map->getName() );
		colorMapMap[ newId ] = map;
	}
	else if( GetItemText(id ) == "カラーマップ" ) {
		const wxTreeItemId objectId = GetItemParent( id );
		VTKObject* object = objectMap[objectId];
		ColorRGBAMap<float>* map = object->createDefaultColorMap();
		const wxString& name = wxGetTextFromUser("カラーマップ名");
		map->setName( name.ToStdString() );
		const wxTreeItemId newId = AppendItem( id, map->getName() );
		colorMapMap[ newId ] = map;		
	}
}

void VTKTree::OnDelete( wxMenuEvent& )
{
	const wxTreeItemId id = GetFocusedItem();

	/*
	if( objectMap.find(id) != objectMap.end() ) {
		VTKObject* object = objectMap[id];
		factory->remove( object );
		Delete(id);
	}
	*/

	if( colorMapMap.find(id) != colorMapMap.end() ) {
		Graphics::ColorRGBAMap<float>* map = colorMapMap[id];
		const wxTreeItemId colorMapId = GetItemParent( id );
		const wxTreeItemId objectId = GetItemParent( colorMapId );
		VTKObject* object = objectMap[objectId];
		object->removeColorMap( map );
		colorMapMap.erase( map );
		delete map;
		Delete(id);
	}
}

void VTKTree::OnItemStateClick(wxTreeEvent& event) {
	OnItemActivated( event );

	const wxTreeItemId id = event.GetItem();

	if( objectMap.find(id) != objectMap.end() ) {
		VTKObject* object = objectMap[id];
		assert( object != nullptr );
		const bool isSelected = object->isSelected();
		SetItemState( id, !isSelected );
		object->setIsSelected( !isSelected );
		view->setRenderingBlocks();
		view->Refresh();
	}

	if( attributeMap.find(id) != attributeMap.end() ) {
		VTKAttributes* attr = attributeMap[id];
		assert( attr != nullptr );
		const bool isSelected = attr->isSelected();
		SetItemState( id, !isSelected );
		attr->setSelected( !isSelected );
		view->setRenderingBlocks();
		view->Refresh();
	}

}

void VTKTree::OnItemActivated(wxTreeEvent& event)
{
	const wxTreeItemId id = event.GetItem();
	
	if( objectMap.find(id) != objectMap.end() ) {
		VTKObject* object = objectMap[id];
		assert( object != nullptr );
		propertyGrid->build( object );
	}

	if( attributeMap.find(id) != attributeMap.end() ) {
		VTKAttributes* attr = attributeMap[id];
		const wxTreeItemId objectId = GetItemParent( GetItemParent( id ) );
		VTKObject* object = objectMap[objectId];
		assert( object != nullptr );
		propertyGrid->build( attr, object );
	}

	if( colorMapMap.find(id) != colorMapMap.end() ) {
		Graphics::ColorRGBAMap<float>* map = colorMapMap[id];
		//const wxTreeItemId objectId = GetItemParent( GetItemParent( id ) );
		//VTKObject* object = objectMap[objectId];
		//const Graphics::ColorRGBAMap<float> map = colorMapMap[objectId];
		ColorMapPanel panel( this, wxDefaultPosition, map );
		panel.ShowModal();
	}
}