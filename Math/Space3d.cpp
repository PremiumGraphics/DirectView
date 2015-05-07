#include "Space3d.h"

#include "Box.h"

using namespace Crystal::Math;

Vector3d Space3d::getStart() const
{
	return start;
}

Vector3d Space3d::getEnd() const
{
	const auto x = start.getX() + resx * size;
	const auto y = start.getY() + resy * size;
	const auto z = start.getZ() + resz * size;
	return Vector3d(x, y, z);
}

Box Space3d::getBoundingBox() const
{
	return Box( start, getEnd());
}
