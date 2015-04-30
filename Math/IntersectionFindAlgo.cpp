#include "IntersectionFindAlgo.h"

#include "../Math/Vector3d.h"
#include "../Math/Box.h"

using namespace Crystal::Math;

bool ScanLineX::hasIntersections(const Box& box) const
{
	return
		(box.getMinY() <= y) && (y <= box.getMaxY()) &&
		(box.getMinZ() <= z) && (z <= box.getMaxZ());
}


std::vector<Vector3d> ScanLineX::getIntersections(const Box& box) const
{
	if (!hasIntersections(box)) {
		return std::vector < Vector3d >() ;
	}

	const std::vector<Vector3d> intersections = {
		Vector3d(box.getMinX(), y, z),
		Vector3d(box.getMaxX(), y, z)
	};
	return intersections;
}

bool ScanLineY::hasIntersections(const Box& box) const
{
	return
		(box.getMinX() <= x) && (x <= box.getMaxX()) &&
		(box.getMinZ() <= z) && (z <= box.getMaxZ());
}

std::vector<Vector3d> ScanLineY::getIntersections(const Box& box) const
{
	if (!hasIntersections(box)) {
		return std::vector < Vector3d >();
	}

	const std::vector<Vector3d> intersections = {
		Vector3d(x, box.getMinY(), z),
		Vector3d(x, box.getMaxY(), z)
	};
	return intersections;

}

/*
bool IntersectionFindAlgo::hasIntersections(const ScanLineX& sline, const std::vector<Box>& boxes) const
{

}
*/

bool sortAlgo(const Vector3d& lhs, const Vector3d& rhs)
{
	return lhs.getX() < rhs.getX();
}

std::vector<Vector3d> IntersectionFindAlgo::getIntersections(const ScanLineX& sline, const std::vector<Box>& boxes) const
{
	Vector3dVector intersections;
	for (const auto& b : boxes) {
		const auto& is = sline.getIntersections(b);
		intersections.insert( intersections.end(), is.begin(), is.end());
	}
	std::sort(intersections.begin(), intersections.end(), sortAlgo);

	//Vector3dVector::iterator iter = intersections.begin();
	
	Vector3dVector::iterator begin = std::adjacent_find(intersections.begin(), intersections.end());
	Vector3dVector::iterator end = std::adjacent_find(begin+1, intersections.end()) -1;

	intersections.erase(begin, end);

	/*
	while (iter != intersections.end() ) {
		iter = intersections.erase(iter);
		iter = std::adjacent_find(intersections.begin(), intersections.end());
	}
	*/
	return intersections;
}