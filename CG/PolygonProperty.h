#ifndef __CRYSTAL_APP_POLYGON_PROPERTY_H__
#define __CRYSTAL_APP_POLYGON_PROPERTY_H__

#include "../Graphics/Polygon.h"
#include "../Graphics/Material.h"
#include "Model.h"

namespace Crystal {
	namespace CG {

class PolygonProperty : public wxPropertyGrid {
public:
	PolygonProperty( wxWindow* parent, const wxSize& size );

//	void build( Graphics::Polygon* polygon, Crystal::Graphics::MaterialCollection* materials );

	void OnDoubleClick( wxPropertyGridEvent& event );

	void OnChanged( wxPropertyGridEvent& event );

private:
	Graphics::Polygon polygon;
};

	}
}

#endif