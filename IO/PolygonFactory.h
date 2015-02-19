#ifndef __CRYSTAL_IO_POLYGON_FACTORY_H__
#define __CRYSTAL_IO_POLYGON_FACTORY_H__

#include "../Graphics/Polygon.h"
#include "OBJFile.h"
#include "STLFile.h"
#include <list>


namespace Crystal {
	namespace IO {

class PolygonGroup {
public:
	PolygonGroup() :
		polygon(nullptr),
		material(nullptr)
	{}

	PolygonGroup(Graphics::Polygon* polygon) :
		polygon(polygon)
	{}

	void setPolygon(Graphics::Polygon* polygon) { this->polygon = polygon; }

	void setMaterial(Graphics::Material* material) { this->material = material; }

	Graphics::Polygon* getPolygon() const { return polygon; }

	Graphics::Material* getMaterial() const { return material; }

private:
	Graphics::Polygon* polygon;
	Graphics::Material* material;
};

typedef std::list<PolygonGroup> PolygonGroupList;

class PolygonFactory {
public:
	PolygonGroupList create(const OBJFile& file);

	Graphics::Polygon* create(const STLFile& file);
};
	}
}

#endif