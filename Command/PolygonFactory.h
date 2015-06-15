#ifndef __CRYSTAL_GRAPHICS_POLYGON_FACTORY_H__
#define __CRYSTAL_GRAPHICS_POLYGON_FACTORY_H__

#include "../Graphics/Polygon.h"

#include "../Math/ScalarSpace.h"
#include "../Math/BitSpace.h"

#include "../Math/MarchingCube.h"

#include "../Util/UnCopyable.h"

#include <memory>

#include "Object.h"
#include "Factory.h"

namespace Crystal {
	namespace Command {

template<typename T>
class PolygonObject : public Object
 {
public:
	PolygonObject(const Graphics::PolygonSPtr<T>& polygon, const unsigned int id) :
		Object(id),
		polygon( polygon )
	{}

	Graphics::PolygonSPtr<T> getPolygon() const { return polygon; }

private:
	Graphics::PolygonSPtr<T> polygon;
};

template<typename T>
using PolygonIdList = std::list < PolygonObject<T> > ;

template<typename T>
class PolygonFactory final : public ObjectFactory, private UnCopyable
{
public:
	PolygonFactory()
	{
		mc.buildTable();
	}

	~PolygonFactory() = default;

	PolygonFactory& clear() {
		ObjectFactory::clear();
		this->polygons.clear();
		return (*this);
	}

	PolygonObject<T> create(const Math::ScalarSpace3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue() );
		}
		return add(polygon);
	}

	PolygonObject<T> create(const Math::BitSpace3d<float>& bs) {
		const auto& triangles = mc.march(bs);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<T> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		return add(polygon);
	}

	Graphics::PolygonSPtr<T> find(const unsigned int id) {
		for (const auto& p : polygons) {
			if (p.getId() == id) {
				return p.getPolygon();
			}
		}
		return nullptr;
	}


	PolygonIdList<T> getPolygons() const { return polygons; }

private:
	PolygonIdList<T> polygons;

	Math::MarchingCube<T> mc;

	PolygonObject<T> add(Graphics::PolygonSPtr<float>& p) {
		this->polygons.push_back( PolygonObject<float>( p, getNextId() ) );
		return polygons.back();
	}

};

template<typename T>
using PolygonFactorySPtr = std::shared_ptr< PolygonFactory<T> > ;

	}
}

#endif