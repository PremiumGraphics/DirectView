#include "HalfEdge.h"

using namespace Crystal::Graphics;

HalfEdgeList HalfEdgeBuilder::buildOpenFromVertices(Face* face)
{
	const VertexVector& vv = vBuilder.getVertices();
	assert(vv.size() >= 1);
	HalfEdgeVector edges;
	for (size_t i = 0; i < vv.size() - 1; ++i ) {
		Vertex* start = vv[i];
		Vertex* end = vv[i+1];
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

HalfEdgeList HalfEdgeBuilder::buildClosedFromVertices(Face* face, const VertexVector& vv)
{
	assert(vv.size() >= 1);
	
	HalfEdgeVector edges;
	for (size_t i = 0; i < vv.size() - 1; ++i) {
		Vertex* start = vv[i];
		Vertex* end = vv[i + 1];
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
		HalfEdge* edge = new HalfEdge(vv.back(), vv.front(), nextId++, face);
		vv.back()->addEdge(edge);
		vv.front()->addEdge(edge);
		edges.push_back(edge);
	}

	edges.front()->setPrev( edges.back() );
	edges.back()->setNext( edges.front() );

	return HalfEdgeList( edges.begin(), edges.end() );
}
