#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

#include "../Math/Triangle.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Graphics {

class Polygon;
typedef std::shared_ptr< Polygon > PolygonSPtr;

class Face {
public:
	Face(const unsigned int id)
		: id(id),
		polygon( nullptr )
	{};


	Face(const HalfEdgeSPtrList& edges, const unsigned int id) :
		edges( edges ),
		id( id ),
		polygon(nullptr)
	{}

	~Face(){}

	unsigned int getId() const { return id; }

	bool isClosed() const { return edges.back()->getEndPosition() == edges.front()->getStartPosition(); }

	bool isOpen() const { return !isClosed(); }

	void setEdges(const HalfEdgeSPtrList& edges) { this->edges = edges; }

	HalfEdgeSPtrList getEdges() const { return edges; }

	VertexSPtrVector<float> getVertices() const {
		VertexSPtrVector<float> vertices;
		for (const HalfEdgeSPtr& e : edges) {
			vertices.push_back(e->getStart());
		}
		return vertices;
	}

	Math::Vector3dVector<float> getTexCoords() const {
		Math::Vector3dVector<float> texCoords;
		for (const auto& e : edges) {
			texCoords.push_back(e->getStart()->getNormal());
			if (e == edges.back() && isOpen()) {
				texCoords.push_back(e->getEnd()->getNormal());
			}
		}
		return texCoords;
	}

	Math::Vector3d<float> getCenter() const {
		Math::Vector3d<float> center;
		const float size = static_cast<float>(getVertices().size());
		for (const auto& v : getVertices()) {
			center += v->getPosition() / size;
		}
		return center;
	}

	PolygonSPtr getPolygon() const { return polygon; }

	void setPolygon(const PolygonSPtr& polygon) { this->polygon = polygon; }

private:
	//VertexSPtrVector vertices;
	HalfEdgeSPtrList edges;
	VertexSPtrVector<float> vertices;
	const unsigned int id;
	PolygonSPtr polygon;
};

typedef std::shared_ptr<Face> FaceSPtr;
typedef std::vector< std::shared_ptr<Face> > FaceSPtrVector;

	}
}

#endif