#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Face
{
public:
	void add(const HalfEdgeSPtr<T>& e) {
		edges.push_back(e);
	}

	//bool isPoint() const { return edges.empty(); }

	bool isLine() const { return edges.size() == 1; }

private:
	HalfEdgeSPtrList<T> edges;
};
	}
}

#endif