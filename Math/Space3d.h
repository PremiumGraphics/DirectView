#ifndef __CRYSTAL_MATH_SPACE_3D_H__
#define __CRYSTAL_MATH_SPACE_3D_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Math {

class Space3d {
public:
	Space3d(const Vector3d& start, unsigned int resx, unsigned int resy, unsigned int resz ) :
		start( start ),
		resx( resx ),
		resy( resy ),
		resz( resz ),
		size( 1.0f )
	{}

	explicit Space3d(const float size) :size( size)
	{
	}

	float getMinSize() const { return size; }

	Vector3d getStart() const;

	Vector3d getEnd() const;

	unsigned int getResX() const { return resx; }

	unsigned int getResY() const { return resy; }

	unsigned int getResZ() const { return resz; }

	Box getBoundingBox() const;

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
	Vector3d start;
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
};

	}
}

#endif