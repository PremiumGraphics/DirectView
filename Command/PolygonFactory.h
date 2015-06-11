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
class PolygonFactory final : private UnCopyable
{
public:
	PolygonFactory() {
		mc.buildTable();
	}

	~PolygonFactory() = default;

	PolygonFactory& add(Graphics::PolygonSPtr<float>& p) {
		this->polygons.push_back(p);
		return (*this);
	}

	PolygonFactory& clear() {
		this->polygons.clear();
		return (*this);
	}

	Graphics::PolygonSPtr<T> create(const Math::ScalarSpace3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue() );
		}
		polygons.push_back(polygon);

		return polygon;
	}

	Graphics::PolygonSPtr<T> create(const Math::BitSpace3d<float>& bs) {
		const auto& triangles = mc.march(bs);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<T> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		polygons.push_back(polygon);

		return polygon;
	}


	Graphics::PolygonSPtrList<T> getPolygons() const { return polygons; }

private:
	Graphics::PolygonSPtrList<T> polygons;

	Math::MarchingCube<T> mc;
};

template<typename T>
using PolygonFactorySPtr = std::shared_ptr< PolygonFactory<T> > ;

	}
}

#endif