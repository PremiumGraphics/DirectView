#ifndef __CRYSTAL_MATH_SCAN_LINE_X_H__
#define __CRYSTAL_MATH_SCAN_LINE_X_H__

#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		class Vector3d;
		class Box;

class ScanLineX {
public:
	ScanLineX() :
		y( 0.0f),
		z( 0.0f)
	{}

	ScanLineX(const float y, const float z) :
		y( y),
		z( z)
	{}

	bool hasIntersections(const Box& box) const;

	std::vector<Vector3d> getIntersections(const Box& box) const;

private:
	float y;
	float z;
};
	}
}

#endif