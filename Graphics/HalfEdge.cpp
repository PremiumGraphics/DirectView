#include "HalfEdge.h"

using namespace Crystal::Graphics;

std::list<HalfEdge*> HalfEdge::createFromVertices(const VertexVector& vertices)
{
	assert(vertices.size() >= 1);
	std::list<HalfEdge*> edges;
	for (Vertex* v : vertices) {
		HalfEdge edge;
		edge.setStart(v);

	}
	return edges;
}
