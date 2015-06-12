#ifndef __CRYSTAL_GRAPHICS_POLYGON_FACTORY_H__
#define __CRYSTAL_GRAPHICS_POLYGON_FACTORY_H__

#include "../Graphics/Polygon.h"

#include "../Math/ScalarSpace.h"
#include "../Math/BitSpace.h"

#include "../Math/MarchingCube.h"

#include "../Util/UnCopyable.h"

#include <memory>

namespace Crystal {
	namespace Command {

template<typename T>
class PolygonId {
public:
	PolygonId(const Graphics::PolygonSPtr<T>& polygon, const unsigned int id) :
		id( id ),
		polygon( polygon )
	{}

	unsigned int getId() const { return id; }

	Graphics::PolygonSPtr<T> getPolygon() const { return polygon; }

private:
	unsigned int id;
	Graphics::PolygonSPtr<T> polygon;
};

template<typename T>
using PolygonIdList = std::list < PolygonId<T> > ;

template<typename T>
class PolygonFactory final : private UnCopyable
{
public:
	PolygonFactory() :
		nextId(0)
	{
		mc.buildTable();
	}

	~PolygonFactory() = default;

	PolygonFactory& clear() {
		this->polygons.clear();
		return (*this);
	}

	PolygonId<T> create(const Math::ScalarSpace3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue() );
		}
		return add(polygon);
	}

	PolygonId<T> create(const Math::BitSpace3d<float>& bs) {
		const auto& triangles = mc.march(bs);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<T> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		return add(polygon);
	}


	PolygonIdList<T> getPolygons() const { return polygons; }

private:
	PolygonIdList<T> polygons;
	unsigned int nextId;

	Math::MarchingCube<T> mc;

	PolygonId<T> add(Graphics::PolygonSPtr<float>& p) {
		this->polygons.push_back( PolygonId<float>( p, nextId++) );
		return polygons.back();
	}

};

template<typename T>
using PolygonFactorySPtr = std::shared_ptr< PolygonFactory<T> > ;

	}
}

#endif