#include "Space2d.h"

using namespace Crystal::Math;

Vector2d<float> Space2d::getStart() const
{
	return start;
}

Vector2d<float> Space2d::getEnd() const
{
	const auto x = start.getX() + resx * sizes.getX();
	const auto y = start.getY() + resy * sizes.getY();
	return Vector2d<float>(x, y);
}

Quad Space2d::getBoundingQuad() const
{
	return Quad(getStart(), getEnd());
}