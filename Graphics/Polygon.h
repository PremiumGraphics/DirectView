#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include <memory>

#include "../Util/UnCopyable.h"

#include "../Math/Vector.h"
#include "../Math/Triangle.h"
#include "../Math/Box.h"
#include "Vertex.h"
#include "Material.h"
#include "ColorRGBA.h"
#include "HalfEdge.h"

namespace Crystal {
	namespace Graphics {
		class Material;

template<typename T>
class Polygon final : private UnCopyable {
public:

	Polygon() = default;

	~Polygon() = default;

	HalfEdgeSPtrList<float> getEdges() const { return edges; }

	VertexSPtrVector<float> getVertices() const { return vertices; }

	/*
	Polygon& add(const Math::Vector3d<float>& v0, const Math::Vector3d<float>& v1, const ColorRGBA<float>& c) {
		const VertexSPtrVector<float> vs = {
			std::make_shared<Vertex<float> >(v0, Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(0, 0, 0), c),
			std::make_shared<Vertex<float> >(v1, Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(0, 0, 0), c)
		};

		vertices.insert(vertices.end(), vs.begin(), vs.end());
		edges.push_back(std::make_shared <HalfEdge<float> >(vs[0], vs[1]));

		return (*this);
	}
	*/

	Polygon& add(const Math::Triangle<T>& t, const ColorRGBA<float>& c) {
		const auto normal = t.getNormal();
		VertexSPtrVector<T> vs;
		vs.push_back(std::make_shared<Vertex<T> >(t.getv0(), normal, Math::Vector3d<float>(0, 0, 0), c));
		vs.push_back(std::make_shared<Vertex<T> >(t.getv1(), normal, Math::Vector3d<float>(0, 0, 0), c));
		vs.push_back(std::make_shared<Vertex<T> >(t.getv2(), normal, Math::Vector3d<float>(0, 0, 0), c));

		const HalfEdgeSPtrList<T>& es = HalfEdge<T>::createClosed(vs);
		edges.insert(edges.end(), es.begin(), es.end());

		vertices.insert(vertices.end(), vs.begin(), vs.end() );

		return (*this);
	}

	//Polygon* add(const Math::Quad)

	Polygon& add(const Math::Box<T>& box, const ColorRGBA<float>& c) {
		const auto minx = box.getMinX();
		const auto miny = box.getMinY();
		const auto minz = box.getMinZ();
		const auto maxx = box.getMaxX();
		const auto maxy = box.getMaxY();
		const auto maxz = box.getMaxZ();
		VertexSPtrVector<T> vs;
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( minx, miny, minz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( maxx, miny, minz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( maxx, maxy, minz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( minx, maxy, minz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( minx, miny, maxz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( maxx, miny, maxz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( maxx, maxy, maxz)));
		vs.push_back(std::make_shared<Vertex<T> >(Math::Vector3d<T>( minx, maxy, maxz)));

		vertices.insert(vertices.end(), vs.begin(), vs.end());

		const HalfEdgeSPtrList<T>& es1 = HalfEdge<T>::createClosed({ vs[0], vs[1], vs[2], vs[3] });
		const HalfEdgeSPtrList<T>& es2 = HalfEdge<T>::createClosed({ vs[4], vs[5], vs[6], vs[7] });
		edges.insert(edges.end(), es1.begin(), es1.end());
		edges.insert(edges.end(), es2.begin(), es2.end());
		edges.push_back( std::make_shared<HalfEdge<T> >(vs[0], vs[4]));
		edges.push_back( std::make_shared<HalfEdge<T> >(vs[1], vs[5]));
		edges.push_back( std::make_shared<HalfEdge<T> >(vs[2], vs[6]));
		edges.push_back(std::make_shared<HalfEdge<T> >(vs[3], vs[7]));

		return (*this);
	}

private:
	VertexSPtrVector<T> vertices;
	HalfEdgeSPtrList<T> edges;
};

template<typename T>
using PolygonSPtr = std::shared_ptr< Polygon<T> >;

template<typename T>
using PolygonSPtrVector = std::vector< PolygonSPtr<T> >;

template<typename T>
using PolygonSPtrList = std::list< PolygonSPtr<T> >;

	}
}

#endif