#include "Polygon.h"

#include "../Math/Matrix3d.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void Polygon::rotateX(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<double>& m = Matrix3d<double>::RotateX(angle * Tolerances::getPrecisePI() / 180.0);
	for (Vector3d& p : positions) {
		p.rotate(m);
	}
	move(1.0 * center);
}

void Polygon::rotateY(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<double>& m = Matrix3d<double>::RotateY(angle * Tolerances::getPrecisePI() / 180.0);
	for (Vector3d& p : positions) {
		p.rotate(m);
	}
	move(1.0 * center);
}

void Polygon::rotateZ(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<double>& m = Matrix3d<double>::RotateZ(angle * Tolerances::getPrecisePI()/ 180.0);
	for (Vector3d& p : positions) {
		p.rotate(m);
	}
	move(1.0 * center);
}

void Polygon::scale(const Vector3d& scale)
{
	move(-1.0 *center);
	for (Math::Vector3d& p : positions) {
		p.scale(scale.getX(), scale.getY(), scale.getZ());
	}
	move(1.0 * center);
}