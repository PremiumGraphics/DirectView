#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "../Graphics/Polygon.h"

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:
	PolygonBuilder() :
		polygon(nullptr)
	{}

	void buildQuad();

	Polygon* getPolygon() { return polygon; }

private:
	Polygon* polygon;
};
	}
}

#endif