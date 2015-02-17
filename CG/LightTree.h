#ifndef __CRYSTAL_APP_LIGHT_TREE_H__
#define __CRYSTAL_APP_LIGHT_TREE_H__

#include <vector>
#include <string>
#include <map>

#include "../Graphics/Light.h"

#include "LightProperty.h"

namespace Crystal {
	namespace CG {
		
class LightTree : public wxTreeCtrl
{
public:
	LightTree
		(
		wxWindow *parent,
		const wxPoint& pos,
		const wxSize& size,
		LightProperty* property,
		std::list<Graphics::Light> lights
		);

	~LightTree();

	void build();

	void OnItemActivated(wxTreeEvent& event);

private:
	void OnItemStateClick(wxTreeEvent& event) {
		/*
		const wxTreeItemId itemId = event.GetItem();
		const std::string& name = GetItemText( itemId ).ToStdString();

		Graphics::Light* l = model->find( name );
		l->isSelected = !l->isSelected;
		SetItemState( itemId, l->isSelected );
		*/
	}

	void OnMenu(wxTreeEvent& event);

	void OnAdd( wxMenuEvent& );

	void OnDelete( wxMenuEvent& ) {
		const wxTreeItemId item = GetFocusedItem();
		Delete(item);
	}

	LightProperty* property;

	std::list<Graphics::Light> lights_;

	typedef std::map<wxTreeItemId, Graphics::Light*> ItemLightMap;
	ItemLightMap map;
};

	}
}

#endif