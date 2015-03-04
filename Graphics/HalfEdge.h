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
		end( nullptr )
	{}

	HalfEdge(Vertex* start, Vertex* end) :
		start( start ),
		end( end )
	{}

	void setPrev(HalfEdge* prev) { this->prev = prev; }

	void setNext(HalfEdge* next) { this->next = next; }

	HalfEdge* getPrev() { return prev; }

	HalfEdge* getNext() { return next; }

	Vertex* getStart() { return start; }

	Vertex* getEnd() { return end; }

	Math::Vector3d getStartPosition() const { return start->getPosition(); }

	Math::Vector3d getEndPosition() const { return end->getPosition(); }

	static std::list<HalfEdge*> createFromVertices(const VertexVector& vertices);

private:
	Vertex* start;
	Vertex* end;
	HalfEdge* prev;
	HalfEdge* next;
};
	}
}

#endif