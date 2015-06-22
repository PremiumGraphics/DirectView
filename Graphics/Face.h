#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Face final
{
public:
	Face()
	{}

	explicit Face(const HalfEdgeSPtrList<T>& edges) {
		set(edges);
	}

	void add(const HalfEdgeSPtr<T>& e) {
		edges.push_back(e);
	}

	void set(const HalfEdgeSPtrList<T>& edges) {
		this->edges = edges;
	}

	//bool isPoint() const { return edges.empty(); }

	bool isLine() const { return edges.size() == 1; }

	HalfEdgeSPtrList<T> getEdges() const { return edges; }

	Math::Vector3d<T> getNormal() const { return edges.front()->getStartVertex()->getNormal(); }

private:
	HalfEdgeSPtrList<T> edges;
};

template<typename T>
using FaceSPtr = std::shared_ptr < Face<T> > ;

template<typename T>
using FaceSPtrList = std::list < FaceSPtr<T> > ;
	}
}

#endif