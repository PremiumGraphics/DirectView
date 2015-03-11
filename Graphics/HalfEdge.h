#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include "../Math/Vector3d.h"
#include "Vertex.h"

#include <list>

namespace Crystal {
	namespace Graphics {

class Vertex;
class Face;

class HalfEdge {
public:
	HalfEdge() :
		prev( nullptr ),
		next( nullptr ),
		start( nullptr ),
		end( nullptr ),
		face(nullptr),
		id( -1 )
	{}

	HalfEdge(Vertex* start, Vertex* end, const unsigned int id, Face* face) :
		start(start),
		end(end),
		face(face),
		id( id )
	{}

	Face* getFace() const { return face; }

	void setFace(Face* f){ this->face = f; }

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

	unsigned int getId() const { return id; }

private:
	Vertex* start;
	Vertex* end;
	HalfEdge* prev;
	HalfEdge* next;
	Face* face;
	const unsigned int id;
};

typedef std::vector<HalfEdge*> HalfEdgeVector;
typedef std::list<HalfEdge*> HalfEdgeList;

class HalfEdgeBuilder
{
public:
	HalfEdgeBuilder(VertexBuilder& vBuilder) :
		nextId(0),
		vBuilder( vBuilder )
	{}

	HalfEdge* build(Vertex* start, Vertex* end, Face* face)
	{
		edges.push_back(new HalfEdge(start, end, nextId++, face));
	}

	HalfEdgeList buildOpenFromVertices(Face* face);

	HalfEdgeList buildClosedFromVertices(Face* face, const VertexVector& vv);

	VertexBuilder& getVertexBuilder() const { return vBuilder; }

private:
	HalfEdgeList edges;
	VertexBuilder& vBuilder;
	unsigned int nextId;
};

	}
}

#endif