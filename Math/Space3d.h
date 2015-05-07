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
		sizes(Vector3d(1.0f, 1.0f, 1.0f))
	{}

	Space3d(unsigned int resx, unsigned int resy, unsigned int resz) : Space3d(Vector3d::Zero(), resx, resy, resz){}

	Vector3d getSizes() const { return sizes; }

	Vector3d getStart() const;

	Vector3d getEnd() const;

	unsigned int getResX() const { return resx; }

	unsigned int getResY() const { return resy; }

	unsigned int getResZ() const { return resz; }

	Box getBoundingBox() const;

	std::vector<int> getHashedIndex(const Vector3d& point) {
		const auto gridx = static_cast<int>(point.getX() / sizes.getX());
		const auto gridy = static_cast<int>(point.getY() / sizes.getY());
		const auto gridz = static_cast<int>(point.getZ() / sizes.getZ());
		return std::vector < int > {gridx, gridy, gridz};
	}

private:
	Vector3dVector positions;
	
	Vector3d start;
	Vector3d sizes;
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
};

	}
}

#endif