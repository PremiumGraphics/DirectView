#include "HalfEdge.h"

using namespace Crystal::Graphics;

HalfEdgeSPtrList HalfEdgeBuilder::buildOpenFromVertices(const VertexSPtrVector& vv)
{
	assert(vv.size() >= 1);
	HalfEdgeVector edges;
	for (size_t i = 0; i < vv.size() - 1; ++i ) {
		const VertexSPtr& start = vv[i];
		const VertexSPtr& end = vv[i+1];
		HalfEdgeSPtr edge( new HalfEdge( start, end, nextId++, face ) );
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
	return HalfEdgeSPtrList(edges.begin(), edges.end());
}

HalfEdgeSPtrList HalfEdgeBuilder::buildClosedFromVertices( const VertexSPtrVector& vv)
{
	assert(vv.size() >= 1);
	
	HalfEdgeVector edges;
	for (size_t i = 0; i < vv.size() - 1; ++i) {
		const VertexSPtr& start = vv[i];
		const VertexSPtr& end = vv[i + 1];
		HalfEdgeSPtr edge( new HalfEdge(start, end, nextId++, face) );
		start->addEdge(edge);
		end->addEdge(edge);
		edges.push_back(edge);
	}

	for (size_t i = 0; i < edges.size() - 1; ++i) {
		edges[i]->setNext(edges[i + 1]);
		edges[i + 1]->setPrev(edges[i]);
	}
	{
		HalfEdgeSPtr edge( new HalfEdge(vv.back(), vv.front(), nextId++, face) );
		vv.back()->addEdge(edge);
		vv.front()->addEdge(edge);
		edges.push_back(edge);
	}

	edges.front()->setPrev( edges.back() );
	edges.back()->setNext( edges.front() );

	return HalfEdgeSPtrList( edges.begin(), edges.end() );
}
