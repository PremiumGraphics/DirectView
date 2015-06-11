#ifndef __CRSYTAL_GRAPHICS_DRAWABLE_FACTORY_H__
#define __CRSYTAL_GRAPHICS_DRAWABLE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "../Graphics/Polygon.h"

#include "../Util/UnCopyable.h"

#include <memory>
#include <tuple>

namespace Crystal{
	namespace Command {

		/*
template<typename T>
using DrawablePoint = std::tuple < unsigned int, Math::Vector3d<T> > ;

template<typename T>
using DrawablePointVector = std::vector < DrawablePoint<T> > ;
*/
/*
template<typename T>
class DrawablePoints
{
	std::vector<float> points;
};
*/

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
	Graphics::PolygonSPtrList<T> polygons;
};

template<typename T>
using DrawableFactorySPtr = std::shared_ptr< DrawableFactory<T> > ;
	}
}

#endif