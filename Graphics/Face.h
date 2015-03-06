#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

#include <vector>

namespace Crystal {
	namespace Graphics {

class Face {
public:
	Face(const unsigned int id) : id(id)
	{};

	Face(const VertexVector& vertices, const std::vector<unsigned int >& vertexIds, const unsigned int id) :
		id(id)
	{
		edges = HalfEdge::createByIndex(vertices, vertexIds);
	}

	Face(const HalfEdgeList& edges, const unsigned int id) :
		edges( edges ),
		id( id )
	{}

	~Face(){
		for (HalfEdge* e : edges) {
			delete e;
		}
	}

	unsigned int getId() const { return id; }

	std::vector<unsigned int> getVertexIds() {
		std::vector<unsigned int> ids;
		for (HalfEdge* edge : edges) {
			ids.push_back( edge->getStart()->getId() );
		}
		return ids;
	}

	bool isClosed() const { return edges.back()->getEndPosition() == edges.front()->getStartPosition(); }

	bool isOpen() const { return !isClosed(); }

	void setEdges(const HalfEdgeList& edges) { this->edges = edges; }

	HalfEdgeList getEdges() const { return edges; }

	Math::Vector3dVector getPositions() const;

	Math::Vector3dVector getNormals() const;

	Math::Vector3dVector getTexCoords() const;

private:
	//VertexVector vertices;
	HalfEdgeList edges;
	const unsigned int id;

};

typedef std::vector<Face*> FaceVector;


	}
}

#endif