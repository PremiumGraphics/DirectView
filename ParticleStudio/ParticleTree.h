#ifndef __CRYSTAL_APP_PARTICLE_TREE_H__
#define __CRYSTAL_APP_PARTICLE_TREE_H__

namespace Crystal {
	namespace CG {

class ParticleTree : public wxTreeCtrl
{
public:
	ParticleTree
		(
		wxWindow *parent,
		const wxPoint& pos,
		const wxSize& size
		//PolygonProperty* property,
		//Graphics::PolygonBuilder& builder
		);

	~ParticleTree();

	void build();

	void OnItemActivated(wxTreeEvent& event);

private:
	void OnItemStateClick(wxTreeEvent& event);

	void OnMenu(wxTreeEvent& event);

	void OnAdd(wxMenuEvent&);

	void OnDelete(wxMenuEvent&);

	void OnClear(wxMenuEvent&);

	//PolygonProperty* property;

	//Graphics::PolygonBuilder& builder;

	//std::map< wxTreeItemId, Graphics::Polygon* > map;
};

	}
}

#endif