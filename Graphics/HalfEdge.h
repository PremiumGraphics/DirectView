#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include <memory>

#include "Vertex.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class HalfEdge
{
public:
	HalfEdge(const VertexSPtr<T>& start, const VertexSPtr<T>& end) :
		start( start ),
		end( end )
	{}

	std::shared_ptr<HalfEdge> getPrev() const { return prev; }

	void setPrev(const std::shared_ptr<HalfEdge>& prev) { this->prev = prev; }

	std::shared_ptr<HalfEdge> getNext() const { return next; }

	void setNext(const std::shared_ptr<HalfEdge>& next) { this->next = next; }

	VertexSPtr<T> getStartVertex() const { return start; }

	VertexSPtr<T> getEndVertex() const { return end; }

	bool isStart() const { return getPrev() == nullptr; }

	bool isEnd() const { return getNext() == nullptr; }

	bool isValid() const { return start != nullptr || end != nullptr; }

	bool isIsolated() const { return (getPrev() == this) && (getNext() == this); }

private:
	const VertexSPtr<T>& start;
	const VertexSPtr<T>& end;

	std::shared_ptr<HalfEdge> prev;
	std::shared_ptr<HalfEdge> next;
};
	}
}

#endif