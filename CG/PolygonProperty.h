#ifndef __CRYSTAL_APP_POLYGON_PROPERTY_H__
#define __CRYSTAL_APP_POLYGON_PROPERTY_H__

#include "../Graphics/Polygon.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace CG {

class PolygonProperty : public wxPropertyGrid {
public:
	PolygonProperty(wxWindow* parent, const wxSize& size, const Graphics::MaterialSPtrList& materials);

	void build( const Graphics::PolygonSPtr& group );

	void OnDoubleClick( wxPropertyGridEvent& event );

	void OnChanged( wxPropertyGridEvent& event );

private:
	Graphics::PolygonSPtr polygon;
	const Graphics::MaterialSPtrList& materials;
};

	}
}

#endif