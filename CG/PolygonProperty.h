#ifndef __CRYSTAL_APP_POLYGON_PROPERTY_H__
#define __CRYSTAL_APP_POLYGON_PROPERTY_H__

#include "../Graphics/Polygon.h"
#include "../Graphics/Material.h"
#include "../Graphics/PolygonGroup.h"

namespace Crystal {
	namespace CG {

class PolygonProperty : public wxPropertyGrid {
public:
	PolygonProperty( wxWindow* parent, const wxSize& size );

	void build( const Graphics::PolygonGroup& group );

	void OnDoubleClick( wxPropertyGridEvent& event );

	void OnChanged( wxPropertyGridEvent& event );

private:
	Graphics::PolygonGroup group;
};

	}
}

#endif