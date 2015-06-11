#ifndef __CRSYTAL_GRAPHICS_DRAWABLE_FACTORY_H__
#define __CRSYTAL_GRAPHICS_DRAWABLE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "../Graphics/Polygon.h"

#include "../Util/UnCopyable.h"

#include <memory>

namespace Crystal{
	namespace Command {

template<typename T>
class DrawableFactory final : private UnCopyable{
public:

	DrawableFactory& clear() {
		this->polygons.clear();
		return (*this);
	}

	Graphics::PolygonSPtr<T> createBoundingBox(const Math::ScalarSpace3d<T>& ss) {
		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		Math::Box<T> bb(ss.getStart(), ss.getEnd());
		polygon->add(bb, Graphics::ColorRGBA<float>::Black());
		polygons.push_back(polygon);
		return polygon;
	}

	Graphics::PolygonSPtr<T> createGridCells(const Math::ScalarSpace3d<T>& ss) {
		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		const auto& cells = ss.toCells();
		for (const auto& c : cells) {
			const auto& space = c.getSpace();
			Math::Box<T> bb(space.getStart(), space.getEnd());
			polygon->add(bb, Graphics::ColorRGBA<float>::Black());
			//polygon->add( )
		}
		polygons.push_back(polygon);
		return polygon;
	}

	Graphics::PolygonSPtrList<T> getPolygons() const { return polygons; }

private:
	Graphics::PolygonSPtrList<T> polygons;
};

template<typename T>
using DrawableFactorySPtr = std::shared_ptr< DrawableFactory<T> > ;
	}
}

#endif