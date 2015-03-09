#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include "../Math/Vector3d.h"
#include "Vertex.h"

#include <list>

namespace Crystal {
	namespace Graphics {

class Vertex;

class HalfEdge {
public:
	HalfEdge() :
		prev( nullptr ),
		next( nullptr ),
		start( nullptr ),
		end( nullptr ),
		id( -1 )
	{}

	HalfEdge(Vertex* start, Vertex* end, const int id) :
		start(start),
		end(end),
		id( id )
	{}

	void setPrev(HalfEdge* prev) { this->prev = prev; }

	void setNext(HalfEdge* next) { this->next = next; }

	HalfEdge* getPrev() { return prev; }

	HalfEdge* getNext() { return next; }

	void setStart(Vertex* start) { this->start = start; }

	void setEnd(Vertex* end) { this->end = end; }

	Vertex* getStart() { return start; }

	Vertex* getEnd() { return end; }

	Math::Vector3d getStartPosition() const { return start->getPosition(); }

	Math::Vector3d getEndPosition() const { return end->getPosition(); }

private:
	Vertex* start;
	Vertex* end;
	HalfEdge* prev;
	HalfEdge* next;
	const unsigned int id;
};

typedef std::vector<HalfEdge*> HalfEdgeVector;
typedef std::list<HalfEdge*> HalfEdgeList;

class HalfEdgeBuilder
{
public:
	HalfEdgeBuilder() : nextId(0)
	{}

	HalfEdge* build(Vertex* start, Vertex* end, const int id)
	{
		edges.push_back(new HalfEdge(start, end, nextId++));
	}

	HalfEdgeList createOpenFromVertices(const VertexVector& vertices);

	HalfEdgeList createClosedFromVertices(const VertexVector& vertices);

	HalfEdgeList createByIndex(const VertexVector& vertices, const std::vector<unsigned int>& indices);

private:
	HalfEdgeList edges;
	unsigned int nextId;
};

	}
}

#endif