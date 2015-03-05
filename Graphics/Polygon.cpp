#include "Polygon.h"

#include "../Math/Matrix3d.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void Polygon::rotateX(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<double>& m = Matrix3d<double>::RotateX(angle * Tolerances::getPrecisePI() / 180.0);
	for (Vertex* v : vertices) {
		v->rotate(m);
	}
	move(1.0 * center);
}

void Polygon::rotateY(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<double>& m = Matrix3d<double>::RotateY(angle * Tolerances::getPrecisePI() / 180.0);
	for (Vertex* v : vertices) {
		v->rotate(m);
	}
	move(1.0 * center);
}

void Polygon::rotateZ(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<double>& m = Matrix3d<double>::RotateZ(angle * Tolerances::getPrecisePI()/ 180.0);
	for (Vertex* v : vertices) {
		v->rotate(m);
	}
	move(1.0 * center);
}

void Polygon::scale(const Vector3d& scale)
{
	move(-1.0 *center);
	for (Vertex* v : vertices) {
		v->scale(scale);
	}
	move(1.0 * center);
}