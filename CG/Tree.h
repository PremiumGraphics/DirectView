#ifndef __CRYSTAL_APP_TREE_H__
#define __CRYSTAL_APP_TREE_H__

#include <vector>
#include <string>
#include <map>
#include <list>

#include "../Graphics/Light.h"

#include "PropertyDialog.h"


#include "../Graphics/Material.h"
#include "../IO/PolygonFactory.h"


#include <memory>

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
		const Graphics::LightBuilderSPtr& builder
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

	void OnDelete(wxMenuEvent&);

	LightProperty* property;

	Graphics::LightBuilderSPtr builder;

	typedef std::map<wxTreeItemId, Graphics::LightSPtr> ItemLightMap;
	ItemLightMap map;
};


class MaterialTree : public wxTreeCtrl
{
public:
	MaterialTree
		(
		wxWindow *parent,
		const wxPoint& pos,
		const wxSize& size,
		MaterialProperty* property,
		const Graphics::MaterialBuilderSPtr& builder
		);

	~MaterialTree();

	void build();

private:
	void OnMenu(wxTreeEvent& event);

	void OnAdd(wxMenuEvent&);

	void OnDelete(wxMenuEvent&);

	void OnItemActivated(wxTreeEvent& event);

	Graphics::MaterialBuilderSPtr builder;

	MaterialProperty* property;

	std::map< wxTreeItemId, Graphics::MaterialSPtr > map;
};

class PolygonProperty;

class PolygonTree : public wxTreeCtrl
{
public:
	PolygonTree
		(
		wxWindow *parent,
		const wxPoint& pos,
		const wxSize& size,
		PolygonProperty* property,
		const Graphics::PolygonBuilderSPtr& builder
		);

	~PolygonTree();

	void build();

	void OnItemActivated(wxTreeEvent& event);

private:
	void OnItemStateClick(wxTreeEvent& event);

	void OnMenu(wxTreeEvent& event);

	void OnAdd(wxMenuEvent&);

	void OnDelete(wxMenuEvent&);

	PolygonProperty* property;

	Graphics::PolygonBuilderSPtr builder;

	std::map< wxTreeItemId, Graphics::PolygonSPtr > map;
};

	}
}


#endif