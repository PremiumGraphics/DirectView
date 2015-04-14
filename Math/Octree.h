#ifndef __CRYSTAL_MATH_OCTREE_H__
#define __CRYSTAL_MATH_OCTREE_H__

#include "Box.h"

#include <list>

namespace Crystal {
	namespace Math {

class Octree {
public:
	Octree(const Box& b):
		box( b )
	{}

private:
	Box box;
	Octree* parent;
	std::list<Octree*> children;
};

	}
}

#endif