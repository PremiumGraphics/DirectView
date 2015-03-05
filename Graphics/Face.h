#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

#include <vector>

namespace Crystal {
	namespace Graphics {

class Face {
public:
	Face(){};

	Face(const VertexVector& vertices, const std::vector<unsigned int >& vertexIds)
	{
		edges = HalfEdge::createByIndex(vertices, vertexIds);
	}

	Face(const HalfEdgeList& edges) :
		edges( edges )
	{}

	~Face(){
		for (HalfEdge* e : edges) {
			delete e;
		}
	}

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

	Math::Vector3dVector getPositions() const {
		Math::Vector3dVector positions;
		for (HalfEdge* e : edges) {
			positions.push_back( e->getStartPosition() );
			if (e == edges.back() && isOpen() ) {
				positions.push_back( e->getEndPosition() );
			}
		}
		return positions;
	}

	Math::Vector3dVector getNormals() const {
		Math::Vector3dVector normals;
		for (HalfEdge* e : edges) {
			normals.push_back(e->getStart()->getNormal() );
		}
		return normals;
	}

private:
	//VertexVector vertices;
	HalfEdgeList edges;

};

typedef std::vector<Face*> FaceVector;


	}
}

#endif