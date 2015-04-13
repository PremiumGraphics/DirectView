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
	const LightBuilderSPtr& builder
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
	Connect( this->GetId(), wxEVT_TREE_ITEM_MENU,			wxTreeEventHandler( LightTree::OnMenu ) );
	Connect( this->GetId(), wxEVT_TREE_ITEM_ACTIVATED,		wxTreeEventHandler( LightTree::OnItemActivated ) );
	Connect( this->GetId(), wxEVT_TREE_STATE_IMAGE_CLICK,	wxTreeEventHandler( LightTree::OnItemStateClick ) );

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

	for( const LightSPtr& l : builder->getLights() ) {
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
	wxMenuItem* clear = menu.Append(wxNewId(), "Clear" );

	Connect( add->GetId(),		wxEVT_COMMAND_MENU_SELECTED,	wxMenuEventHandler( LightTree::OnAdd ) );
	Connect( del->GetId(),		wxEVT_COMMAND_MENU_SELECTED,	wxMenuEventHandler( LightTree::OnDelete ) );	
	Connect( clear->GetId(),	wxEVT_COMMAND_MENU_SELECTED,	wxMenuEventHandler(LightTree::OnClear));

	PopupMenu( &menu, event.GetPoint() );

	event.Skip();
}

void LightTree::OnAdd(wxMenuEvent&)
{
	const wxString& str = wxGetTextFromUser("Name");
	LightSPtr p = builder->build();
	p->setName(str.ToStdString());
	this->build();

	build();

}

void LightTree::OnDelete(wxMenuEvent&)
{
	const wxTreeItemId item = GetFocusedItem();
	LightSPtr l = map[item];
	builder->remove(l);
	Delete(item);
}

void LightTree::OnClear(wxMenuEvent&)
{
	builder->clear();
	map.clear();
	DeleteChildren(GetRootItem());
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
MaterialBuilder& builder
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

	for (Material* m : builder.getMaterials()) {
		const wxTreeItemId id = AppendItem(root, m->getName());
		map[id] = m;
	}
}

void MaterialTree::OnMenu(wxTreeEvent& event)
{
	wxMenu menu;

	wxMenuItem* add = menu.Append(wxNewId(), "Add");
	wxMenuItem* del = menu.Append(wxNewId(), "Delete");
	wxMenuItem* clear = menu.Append(wxNewId(), "Clear");

	Connect(add->GetId(),	wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(MaterialTree::OnAdd));
	Connect(del->GetId(),	wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(MaterialTree::OnDelete));
	Connect(clear->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxMenuEventHandler(MaterialTree::OnClear));

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
	Material* m = map[id];
	property->setValue(m);
}

void MaterialTree::OnAdd(wxMenuEvent&)
{
	const wxString& str = wxGetTextFromUser("Name");
	Material* m = builder.build();
	m->setName(str.ToStdString());
	build();
}

void MaterialTree::OnDelete(wxMenuEvent&)
{
	const wxTreeItemId item = GetFocusedItem();
	if (item == GetRootItem()) {
		return;
	}
	map.erase(item);
	Delete(item);
}

void MaterialTree::OnClear(wxMenuEvent&)
{
	builder.clear();
	map.clear();
	DeleteChildren( GetRootItem() );
}