#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include <memory>

#include "../Util/UnCopyable.h"

#include "../Math/Vector.h"
#include "../Math/Triangle.h"
#include "Vertex.h"
#include "Material.h"

namespace Crystal {
	namespace Graphics {
		class Material;

class Polygon final : private UnCopyable {
public:

	Polygon() = default;

	~Polygon() = default;

	VertexSPtrVector<float> getVertices() const { return vertices; }

	Polygon& add(const Math::Triangle<float>& t) {
		VertexSPtrVector<float> vs;
		vs.push_back(std::make_shared<Vertex<float> >(t.getv0() ));
		vs.push_back(std::make_shared<Vertex<float> >(t.getv1() ));
		vs.push_back(std::make_shared<Vertex<float> >(t.getv2() ));

		/*
		HalfEdgeSPtrList edges;
		edges.push_back( vs[0]);
		edges.push_back(vs[1])
		*/

		//faces.push_back( std::make_shared<Face>(vs) );

		vertices.insert(vertices.end(), vs.begin(), vs.end() );

		return (*this);
	}


private:
	VertexSPtrVector<float> vertices;
};

typedef std::shared_ptr< Polygon > PolygonSPtr;
typedef std::vector< PolygonSPtr > PolygonSPtrVector;
typedef std::list< PolygonSPtr > PolygonSPtrList;

	}
}

#endif