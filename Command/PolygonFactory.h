#ifndef __CRYSTAL_GRAPHICS_POLYGON_FACTORY_H__
#define __CRYSTAL_GRAPHICS_POLYGON_FACTORY_H__

#include "../Graphics/Polygon.h"

#include "../Math/ScalarSpace.h"
#include "../Math/BitSpace.h"

#include "../Math/MarchingCube.h"

namespace Crystal {
	namespace Command {

class PolygonFactory final
{
public:
	PolygonFactory() {
		mc.buildTable();
	}

	~PolygonFactory() = default;

	PolygonFactory& add(Graphics::PolygonSPtr& p) {
		this->polygons.push_back(p);
		return (*this);
	}

	PolygonFactory& clear() {
		this->polygons.clear();
		return (*this);
	}

	Graphics::PolygonSPtr create(const Math::ScalarSpace3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
		for (const auto t : triangles) {
			//p.add(t, Graphics::ColorRGBA<float>::Blue() );
			polygon->add(t.getv0(), t.getv1(), Graphics::ColorRGBA<float>::Blue());
			polygon->add(t.getv1(), t.getv2(), Graphics::ColorRGBA<float>::Blue());
			polygon->add(t.getv2(), t.getv0(), Graphics::ColorRGBA<float>::Blue());
		}
		polygons.push_back(polygon);

		return polygon;
	}

	Graphics::PolygonSPtr create(const Math::BitSpace3d<float>& bs) {
		const auto& triangles = mc.march(bs);

		Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
		for (const auto t : triangles) {
			//p.add(t, Graphics::ColorRGBA<float>::Blue() );
			polygon->add(t.getv0(), t.getv1(), Graphics::ColorRGBA<float>::Blue());
			polygon->add(t.getv1(), t.getv2(), Graphics::ColorRGBA<float>::Blue());
			polygon->add(t.getv2(), t.getv0(), Graphics::ColorRGBA<float>::Blue());
		}
		polygons.push_back(polygon);

		return polygon;
	}


	Graphics::PolygonSPtrList getPolygons() const { return polygons; }

private:
	Graphics::PolygonSPtrList polygons;

	Math::MarchingCube<float> mc;
};

	}
}

#endif