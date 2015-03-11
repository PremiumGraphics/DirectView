#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include "../Math/Vector3d.h"
#include "Vertex.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Graphics {

class Vertex;
class Face;

class HalfEdge;
typedef std::shared_ptr< HalfEdge > HalfEdgeSPtr;


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

	void setPrev(const HalfEdgeSPtr& prev) { this->prev = prev; }

	void setNext(const HalfEdgeSPtr& next) { this->next = next; }

	HalfEdgeSPtr getPrev() { return prev; }

	HalfEdgeSPtr getNext() { return next; }

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
	HalfEdgeSPtr prev;
	HalfEdgeSPtr next;
	Face* face;
	const unsigned int id;
};


typedef std::vector< HalfEdgeSPtr > HalfEdgeVector;
typedef std::list< HalfEdgeSPtr > HalfEdgeList;

class HalfEdgeBuilder
{
public:
	HalfEdgeBuilder(VertexBuilder& vBuilder) :
		nextId(0),
		vBuilder( vBuilder ),
		face( nullptr )
	{}

	Face* getFace() const { return face; }

	void setFace(Face* f) { this->face = f; }

	HalfEdge* build(Vertex* start, Vertex* end )
	{
		edges.push_back( HalfEdgeSPtr( new HalfEdge(start, end, nextId++, face )) );
	}

	HalfEdgeList buildOpenFromVertices();

	HalfEdgeList buildClosedFromVertices(const VertexVector& vv);

	VertexBuilder& getVertexBuilder() const { return vBuilder; }

private:
	HalfEdgeList edges;
	VertexBuilder& vBuilder;
	unsigned int nextId;
	Face* face;
};

	}
}

#endif