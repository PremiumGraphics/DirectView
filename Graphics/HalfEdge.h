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
typedef std::shared_ptr< Face > FaceSPtr;

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

	HalfEdge(const VertexSPtr start, const VertexSPtr end, const unsigned int id, FaceSPtr face) :
		start(start),
		end(end),
		face(face),
		id( id )
	{
		start->addEdge(this);
		end->addEdge(this);
	}

	FaceSPtr getFace() const { return face; }

	void setFace(const FaceSPtr& f) { this->face = f; }

	void setPrev(const HalfEdgeSPtr& prev) { this->prev = prev; }

	void setNext(const HalfEdgeSPtr& next) { this->next = next; }

	HalfEdgeSPtr getPrev() { return prev; }

	HalfEdgeSPtr getNext() { return next; }

	void setStart(VertexSPtr start) { this->start = start; }

	void setEnd(VertexSPtr end) {
		end->removeEdge(this);
		this->end = end;
		this->end->addEdge(this);
	}

	VertexSPtr getStart() { return start; }

	VertexSPtr getEnd() { return end; }

	Math::Vector3d getStartPosition() const { return start->getPosition(); }

	Math::Vector3d getEndPosition() const { return end->getPosition(); }

	unsigned int getId() const { return id; }


private:
	VertexSPtr start;
	VertexSPtr end;
	HalfEdgeSPtr prev;
	HalfEdgeSPtr next;
	FaceSPtr face;
	const unsigned int id;
};


typedef std::vector< HalfEdgeSPtr > HalfEdgeVector;
typedef std::list< HalfEdgeSPtr > HalfEdgeSPtrList;


	}
}

#endif