#ifndef __CRYSTAL_GRAPHICS_POLYGON_GROUP_H__
#define __CRYSTAL_GRAPHICS_POLYGON_GROUP_H__

#include <list>

namespace Crystal {
	namespace Graphics {

class Polygon;
class Material;

class PolygonGroup {
public:
	PolygonGroup() :
		polygon(nullptr),
		material(nullptr)
	{}

	PolygonGroup(Polygon* polygon) :
		polygon(polygon),
		material(nullptr)
	{}

	void setPolygon(Polygon* polygon) { this->polygon = polygon; }

	void setMaterial(Material* material) { this->material = material; }

	Polygon* getPolygon() const { return polygon; }

	Material* getMaterial() const { return material; }

private:
	Polygon* polygon;
	Material* material;
};

typedef std::list<PolygonGroup> PolygonGroupList;


	}
}

#endif