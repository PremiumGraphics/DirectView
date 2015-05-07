#include "Space3d.h"

#include "Box.h"

using namespace Crystal::Math;

Vector3d Space3d::getStart() const
{
	return start;
}

Vector3d Space3d::getEnd() const
{
	const auto x = start.getX() + resx * sizes.getX();
	const auto y = start.getY() + resy * sizes.getY();
	const auto z = start.getZ() + resz * sizes.getZ();
	return Vector3d(x, y, z);
}

Box Space3d::getBoundingBox() const
{
	return Box( start, getEnd());
}
