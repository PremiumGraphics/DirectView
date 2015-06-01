#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include "Vertex.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class HalfEdge
{
public:
	HalfEdge(const VertexSPtr& start, const VertexSPtr& end) :
		start( start ),
		end( end )
	{}

	VertexSPtr<T> getStart() const { return start; }

	VertexSPtr<T> getEnd() const { return end; }

private:
	const VertexSPtr<T>& start;
	const VertexSPtr<T>& end;
};
	}
}

#endif