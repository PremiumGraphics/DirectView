#include "HalfEdge.h"

using namespace Crystal::Graphics;

HalfEdgeList HalfEdgeBuilder::createOpenFromVertices(const VertexVector& vertices, Face* face)
{
	assert(vertices.size() >= 1);
	HalfEdgeVector edges;
	for (size_t i = 0; i < vertices.size() - 1; ++i ) {
		Vertex* start = vertices[i];
		Vertex* end = vertices[i+1];
		HalfEdge* edge = new HalfEdge( start, end, nextId++, face );
		start->addEdge(edge);
		end->addEdge(edge);
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

HalfEdgeList HalfEdgeBuilder::createClosedFromVertices(const VertexVector& vertices, Face* face)
{
	assert(vertices.size() >= 1);
	
	HalfEdgeVector edges;
	for (size_t i = 0; i < vertices.size() - 1; ++i) {
		Vertex* start = vertices[i];
		Vertex* end = vertices[i + 1];
		HalfEdge* edge = new HalfEdge(start, end, nextId++, face);
		start->addEdge(edge);
		end->addEdge(edge);
		edges.push_back(edge);
	}

	for (size_t i = 0; i < edges.size() - 1; ++i) {
		edges[i]->setNext(edges[i + 1]);
		edges[i + 1]->setPrev(edges[i]);
	}
	{
		HalfEdge* edge = new HalfEdge(vertices.back(), vertices.front(), nextId++, face);
		vertices.back()->addEdge(edge);
		vertices.front()->addEdge(edge);
		edges.push_back(edge);
	}

	edges.front()->setPrev( edges.back() );
	edges.back()->setNext( edges.front() );

	return HalfEdgeList( edges.begin(), edges.end() );
}
