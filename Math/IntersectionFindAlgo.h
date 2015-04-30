#ifndef __CRYSTAL_MATH_INTERSECTION_FINDL_ALGO_H__
#define __CRYSTAL_MATH_INTERSECTION_FINDL_ALGO_H__

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

class ScanLineY {
public:
	ScanLineY() :
		x(0.0f),
		z(0.0f)
	{}

	ScanLineY(const float x, const float z) :
		x(x),
		z(z)
	{}

	bool hasIntersections(const Box& box) const;

	std::vector<Vector3d> getIntersections(const Box& box) const;

private:
	float x;
	float z;
};

class IntersectionFindAlgo
{
public:
	bool hasIntersections(const ScanLineX& sline, const std::vector<Box>& boxes) const;

	std::vector<Vector3d> getIntersections(const ScanLineX& sline, const std::vector<Box>& boxes) const;

};

class BoxBooleanAlgo
{
public:
	std::vector<Box> createUnion(const ScanLineX& sline, const std::vector<Box>& boxes) const;
};

/*
class Slice
{
	
private:
	std::vector< std::vector< float > > slice;
};
*/
	}
}

#endif