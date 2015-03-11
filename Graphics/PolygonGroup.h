#ifndef __CRYSTAL_GRAPHICS_POLYGON_GROUP_H__
#define __CRYSTAL_GRAPHICS_POLYGON_GROUP_H__

#include <list>
#include <memory>

#include "Polygon.h"

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

	PolygonGroup(const PolygonSPtr& polygon) :
		polygon(polygon),
		material(nullptr)
	{}

	void setPolygon(const PolygonSPtr& polygon) { this->polygon = polygon; }

	void setMaterial(Material* material) { this->material = material; }

	std::shared_ptr< Polygon > getPolygon() const { return polygon; }

	Material* getMaterial() const { return material; }

private:
	std::shared_ptr< Polygon > polygon;
	Material* material;
};

typedef std::list<PolygonGroup> PolygonGroupList;


	}
}

#endif