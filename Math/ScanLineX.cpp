#include "ScanLineX.h"

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
	if (hasIntersections(box)) {
		return std::vector < Vector3d >() ;
	}

	const std::vector<Vector3d> intersections = {
		Vector3d(box.getMinX(), y, z),
		Vector3d(box.getMaxX(), y, z)
	};
	return intersections;
}