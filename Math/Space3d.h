#ifndef __CRYSTAL_MATH_SPACE_3D_H__
#define __CRYSTAL_MATH_SPACE_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Space3d {
public:
	Space3d(const float size) :size( size)
	{
	}

	void add(const Vector3d& v) {
		positions.push_back(v);
	}

	float getMinSize() const { return size; }

	std::vector<int> getHashedIndex(const Vector3d& point) {
		const float effectLength = size;
		int gridx = static_cast<int>(point.getX() / effectLength);
		int gridy = static_cast<int>(point.getY() / effectLength);
		int gridz = static_cast<int>(point.getZ() / effectLength);
		return std::vector < int > {gridx, gridy, gridz};
	}

private:
	Vector3dVector positions;
	float size;
};

	}
}

#endif