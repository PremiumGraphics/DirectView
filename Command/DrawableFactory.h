#ifndef __CRSYTAL_GRAPHICS_DRAWABLE_FACTORY_H__
#define __CRSYTAL_GRAPHICS_DRAWABLE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "PolygonFactory.h"

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

	PolygonObject<T> createBoundingBox(const Math::ScalarSpace3d<T>& ss) {
		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		Math::Box<T> bb(ss.getStart(), ss.getEnd());
		polygon->add(bb, Graphics::ColorRGBA<float>::Black());
		return add(polygon);
	}

	PolygonObject<T> createGridCells(const Math::ScalarSpace3d<T>& ss) {
		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		const auto& cells = ss.toCells();
		for (const auto& c : cells) {
			const auto& space = c.getSpace();
			Math::Box<T> bb(space.getStart(), space.getEnd());
			polygon->add(bb, Graphics::ColorRGBA<float>::Black());
			//polygon->add( )
		}
		return add(polygon);
	}

	PolygonIdList<T> getPolygons() const { return polygons; }

	/*
	void toPoints(const Graphics::VertexSPtrVector<T>& vs) {
		for (const auto& v : vs) {
			DrawablePoint<T> p( v->getId(), v->getPoint());
			points.push_back(p);
		}
	}
	*/

private:
	//DrawablePointVector<T> points;
	Math::TriangleVector<T> triangles;
	PolygonIdList<T> polygons;

	unsigned int nextId;

	PolygonObject<T> add(const Graphics::PolygonSPtr<T>& p) {
		polygons.push_back(PolygonObject<T>(p, nextId++));
		return polygons.back();
	}
};

template<typename T>
using DrawableFactorySPtr = std::shared_ptr< DrawableFactory<T> > ;
	}
}

#endif