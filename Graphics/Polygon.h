#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include <memory>

#include "../Util/UnCopyable.h"

#include "../Math/Vector.h"
#include "../Math/Triangle.h"
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

	Polygon& add(const Math::Triangle<float>& t, const ColorRGBA<float>& c) {
		VertexSPtrVector<float> vs;
		const auto normal = t.getNormal();
		vs.push_back(std::make_shared<Vertex<float> >(t.getv0(), normal, Math::Vector3d<float>(0,0,0), c));
		vs.push_back(std::make_shared<Vertex<float> >(t.getv1(), normal, Math::Vector3d<float>(0,0,0), c));
		vs.push_back(std::make_shared<Vertex<float> >(t.getv2(), normal, Math::Vector3d<float>(0,0,0), c));

		const HalfEdgeSPtrList<float>& es = HalfEdge<float>::createClosed(vs);
		edges.insert(edges.end(), es.begin(), es.end());

		vertices.insert(vertices.end(), vs.begin(), vs.end() );

		return (*this);
	}

	std::vector<float> toPositionArray() const {
		std::vector<float> positions;
		for (const auto& v : vertices) {
			const auto& ps = v->getPosition().toArray();
			positions.insert(positions.end(), ps.begin(), ps.end());
		}
		return positions;
	}

	std::vector<float> toNormalArray() const {
		std::vector<float> normals;
		for (const auto& v : vertices) {
			const auto& ns = v->getNormal().toArray();
			normals.insert(normals.end(), ns.begin(), ns.end());
		}
		return normals;
	}

	std::vector<float> toColorArray() const {
		std::vector<float> results;
		for (const auto& v : vertices) {
			const auto& vs = v->getColor().toArray3();
			results.insert(results.end(), vs.begin(), vs.end());
		}
		return results;
	}


private:
	VertexSPtrVector<float> vertices;
	HalfEdgeSPtrList<float> edges;
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