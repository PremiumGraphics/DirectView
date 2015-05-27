#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include "../Math/Vector3d.h"
#include "Vertex.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Graphics {

class HalfEdge;
typedef std::shared_ptr< HalfEdge > HalfEdgeSPtr;

class HalfEdge {
public:
	HalfEdge() :
		prev( nullptr ),
		next( nullptr ),
		start( nullptr ),
		end( nullptr ),
		id( -1 )
	{}

	HalfEdge(const VertexSPtr<float>& start, const VertexSPtr<float>& end, const unsigned int id) :
		start(start),
		end(end),
		id( id )
	{
	}

	void setPrev(const HalfEdgeSPtr& prev) { this->prev = prev; }

	void setNext(const HalfEdgeSPtr& next) { this->next = next; }

	HalfEdgeSPtr getPrev() { return prev; }

	HalfEdgeSPtr getNext() { return next; }

	VertexSPtr<float> getStart() { return start; }

	VertexSPtr<float> getEnd() { return end; }

	Math::Vector3d<float> getStartPosition() const { return start->getPosition(); }

	Math::Vector3d<float> getEndPosition() const { return end->getPosition(); }

	unsigned int getId() const { return id; }


private:
	VertexSPtr<float> start;
	VertexSPtr<float> end;
	HalfEdgeSPtr prev;
	HalfEdgeSPtr next;
	const unsigned int id;
};


typedef std::vector< HalfEdgeSPtr > HalfEdgeVector;
typedef std::list< HalfEdgeSPtr > HalfEdgeSPtrList;


	}
}

#endif