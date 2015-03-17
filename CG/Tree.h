#ifndef __CRYSTAL_APP_TREE_H__
#define __CRYSTAL_APP_TREE_H__

#include <vector>
#include <string>
#include <map>

#include "../Graphics/Light.h"

#include "PropertyDialog.h"

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
		Graphics::LightSPtrList& lights
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

	Graphics::LightSPtrList& lights_;

	typedef std::map<wxTreeItemId, Graphics::LightSPtr> ItemLightMap;
	ItemLightMap map;
};

	}
}

#endif

#ifndef __CRYSTAL_APP_MATERIAL_TREE_H__
#define __CRYSTAL_APP_MATERIAL_TREE_H__

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "../Graphics/Material.h"
#include "PropertyDialog.h"


namespace Crystal {
	namespace CG {

		class MaterialTree : public wxTreeCtrl
		{
		public:
			MaterialTree
				(
				wxWindow *parent,
				const wxPoint& pos,
				const wxSize& size,
				MaterialProperty* property,
				Graphics::MaterialBuilderSPtr& builder
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

	}
}

#endif