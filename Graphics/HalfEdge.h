#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include <memory>
#include <list>

#include "Vertex.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class HalfEdge
{
public:
	HalfEdge() :
		start(nullptr),
		end(nullptr)
	{}

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

	static std::list< std::shared_ptr<HalfEdge> > createOpen(const VertexSPtrVector<T>& vertices ) {
		if (vertices.size() < 2) {
			return std::list< std::shared_ptr<HalfEdge> >();
		}
		std::list< std::shared_ptr<HalfEdge> > edges;
		for (size_t i = 0; i < vertices.size() - 1; ++i) {
			edges.push_back(std::make_shared< HalfEdge >(vertices[i], vertices[i + 1]));
		}
		return edges;
	}

	static std::list< std::shared_ptr<HalfEdge> > createClosed(const VertexSPtrVector<T>& vertices) {
		if (vertices.size() < 2) {
			return std::list< std::shared_ptr<HalfEdge> >();
		}
		std::list< std::shared_ptr<HalfEdge> > edges = createOpen(vertices);
		const VertexSPtr<T>& v1 = vertices.front();
		const VertexSPtr<T>& v2 = vertices.back();
		edges.push_back(std::make_shared< HalfEdge>(v2, v1));
		return edges;
	}

private:
	const VertexSPtr<T> start;
	const VertexSPtr<T> end;

	std::shared_ptr<HalfEdge> prev;
	std::shared_ptr<HalfEdge> next;
};

template<typename T>
using HalfEdgeSPtr = std::shared_ptr < HalfEdge<T> > ;

template<typename T>
using HalfEdgeSPtrList = std::list < HalfEdgeSPtr<T> > ;
	}
}

#endif