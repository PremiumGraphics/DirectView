#ifndef __CRYSTAL_MATH_VOXEL_H__
#define __CRYSTAL_MATH_VOXEL_H__

#include "../Math/Box.h"

namespace Crystal {
	namespace Math {

class Voxel {
public:
	Voxel(const Box& b) :
		box(b),
		parent( nullptr )
	{}

	Voxel(const Box& b, Voxel* parent) :
		box(b),
		parent(parent)
	{}


	Box getBox() const { return box; }
	
	Voxel* getParent() { return parent; }

	std::vector < Voxel* > getChildren() { return children; }

	std::vector< Voxel* > createChildren();

private:
	Box box;

	Voxel* parent;
	std::vector < Voxel* > children;
};

	}
}

#endif