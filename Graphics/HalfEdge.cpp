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
		//start->addEdge(edge.get());
		//end->addEdge(edge.get());
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
		//start->addEdge(edge.get());
		//end->addEdge(edge.get());
		edges.push_back(edge);
	}

	for (size_t i = 0; i < edges.size() - 1; ++i) {
		edges[i]->setNext(edges[i + 1]);
		edges[i + 1]->setPrev(edges[i]);
	}
	{
		HalfEdgeSPtr edge( new HalfEdge(vv.back(), vv.front(), nextId++, face) );
		//vv.back()->addEdge(edge.get());
		//vv.front()->addEdge(edge.get());
		edges.push_back(edge);
	}

	edges.front()->setPrev( edges.back() );
	edges.back()->setNext( edges.front() );

	return HalfEdgeSPtrList( edges.begin(), edges.end() );
}

HalfEdgeSPtr HalfEdgeBuilder::insert(const HalfEdgeSPtr& edge, const VertexSPtr& v)
{
	//HalfEdgeSPtr edge1(new HalfEdge(start, v, id, face));
	const HalfEdgeSPtr& next = edge->getNext();

	VertexSPtr end = edge->getEnd();
	edge->setEnd(v);
	HalfEdgeSPtr edge2(new HalfEdge(v, end, nextId++, face));
	edge2->setNext(next);
	if (next != nullptr) {
		next->setPrev(edge2);
	}

	return edge2;
}