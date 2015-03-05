#include "HalfEdge.h"

using namespace Crystal::Graphics;

HalfEdgeList HalfEdge::createOpenFromVertices(const VertexVector& vertices)
{
	assert(vertices.size() >= 1);
	HalfEdgeVector edges;
	for (size_t i = 0; i < vertices.size() - 1; ++i ) {
		Vertex* start = vertices[i];
		Vertex* end = vertices[i+1];
		HalfEdge* edge = new HalfEdge( start, end );
		edges.push_back(edge);
	}
	for (size_t i = 0; i < edges.size() - 1; ++i ) {
		edges[i]->setNext(edges[i + 1]);
		edges[i + 1]->setPrev(edges[i]);
	}
	edges.front()->setPrev(nullptr);
	edges.back()->setNext(nullptr);
	return HalfEdgeList(edges.begin(), edges.end());
}

HalfEdgeList HalfEdge::createClosedFromVertices(const VertexVector& vertices)
{
	assert(vertices.size() >= 1);
	
	HalfEdgeVector edges;
	for (size_t i = 0; i < vertices.size() - 1; ++i) {
		Vertex* start = vertices[i];
		Vertex* end = vertices[i + 1];
		HalfEdge* edge = new HalfEdge(start, end);
		edges.push_back(edge);
	}

	{
		HalfEdge* edge = new HalfEdge(vertices.back(), vertices.front());
		edges.push_back(edge);
	}
	return HalfEdgeList( edges.begin(), edges.end() );
}

HalfEdgeList HalfEdge::createByIndex(const VertexVector& vertices, const std::vector<unsigned int>& indices)
{
	VertexVector vs;
	for ( const unsigned int i : indices) {
		vs.push_back(vertices[i]);
	}
	return createClosedFromVertices(vs);
}
