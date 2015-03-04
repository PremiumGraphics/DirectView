#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

#include <vector>

namespace Crystal {
	namespace Graphics {

class Face {
public:
	Face(){};

	Face(const std::vector<unsigned int >& vertexIds) :
		vertexIds(vertexIds)
	{}

	Face(const std::vector<unsigned int >& vertexIds, const std::vector<unsigned int>& normalIds) :
		vertexIds(vertexIds),
		normalIds(normalIds)
	{}

	Face(const HalfEdgeList& edges) :
		edges( edges )
	{}

	bool isClosed() const { return edges.back()->getEndPosition() == edges.front()->getStartPosition(); }

	bool isOpen() const { return !isClosed(); }

	void setNormalIds(const std::vector<unsigned int>& normalIds) { this->normalIds = normalIds; }

	std::vector<unsigned int> getNormalIds() const { return normalIds; }

	void setVertexIds(const std::vector<unsigned int >& vertexIds) { this->vertexIds = vertexIds; }

	std::vector< unsigned int > getVertexIds() const { return vertexIds; }

	bool operator==(const Face& rhs) const {
		return
			vertexIds == rhs.vertexIds &&
			normalIds == rhs.normalIds;
	}

	void setEdges(const HalfEdgeList& edges) { this->edges = edges; }

	HalfEdgeList getEdges() const { return edges; }

private:
	//VertexVector vertices;
	HalfEdgeList edges;
	std::vector< unsigned int > vertexIds;
	std::vector< unsigned int > normalIds;
};

typedef std::vector<Face> FaceVector;


	}
}

#endif