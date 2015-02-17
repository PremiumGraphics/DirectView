#ifndef __CRYSTAL_APP_VTK_TREE_H__
#define __CRYSTAL_APP_VTK_TREE_H__

#include <vector>
#include <string>

#include "../IO/VTKObject.h"
#include "../IO/VTKObjectFactory.h"

#include "../Graphics/ColorRGBAMap.h"

#include <map>


namespace Crystal {
	namespace App {
		class VTKPropertyGrid;
		class View;

typedef std::map< wxTreeItemId, IO::VTKObject* > ItemVTKObjectMap;
typedef std::map< wxTreeItemId, IO::VTKAttributes* > ItemVTKAttributeMap;
typedef std::map< wxTreeItemId, Graphics::ColorRGBAMap<float>* > ItemColorMap;

class VTKTree : public wxTreeCtrl
{
public:
	VTKTree
		(
		wxWindow *parent,
		View* view,
		const wxPoint& pos,
		const wxSize& size,
		IO::VTKObjectFactory* factory,
		VTKPropertyGrid* propertyGrid
		);

	~VTKTree();

	void build();

private:
	void OnMenu(wxTreeEvent& event);

	void OnAdd( wxMenuEvent& );

	void OnDelete( wxMenuEvent& );

	void OnItemStateClick(wxTreeEvent& event);

	void OnItemActivated(wxTreeEvent& event);

	VTKPropertyGrid* propertyGrid;

	IO::VTKObjectFactory* factory;

	ItemVTKObjectMap objectMap;
	ItemVTKAttributeMap attributeMap;
	ItemColorMap colorMapMap;
	View* view;
};


	}
}

#endif