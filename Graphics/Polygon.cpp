#include "Polygon.h"

#include "../Math/Matrix3d.h"
#include "../Math/Box.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void Polygon::rotateX(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<float>& m = Matrix3d<float>::RotateX(angle * Tolerance<double>::getPI() / 180.0);
	for (const VertexSPtr& v : vertices) {
		v->rotate(m);
	}
	move(1.0 * center);
}

void Polygon::rotateY(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<float>& m = Matrix3d<float>::RotateY(angle * Tolerance<double>::getPI() / 180.0);
	for (const VertexSPtr v : vertices) {
		v->rotate(m);
	}
	move(1.0 * center);
}

void Polygon::rotateZ(const double angle)
{
	move(-1.0 *center);
	const Matrix3d<float>& m = Matrix3d<float>::RotateZ(angle * Tolerance<double>::getPI() / 180.0);
	for (const VertexSPtr& v : vertices) {
		v->rotate(m);
	}
	move(1.0 * center);
}

void Polygon::scale(const Vector3d& scale)
{
	move(-1.0 *center);
	for (const VertexSPtr& v : vertices) {
		v->scale(scale);
	}
	move(1.0 * center);
}

#include <algorithm>

Box Polygon::getBoundingBox() const
{
	float minx = FLT_MAX;
	float miny = FLT_MAX;
	float minz = FLT_MAX;
	float maxx = -FLT_MAX;
	float maxy = -FLT_MAX;
	float maxz = -FLT_MAX;
	for (const VertexSPtr& v : vertices) {
		const float x = v->getPosition().getX();
		const float y = v->getPosition().getY();
		const float z = v->getPosition().getZ();
		minx = std::min<float>( minx, x );
		miny = std::min<float>( miny, y );
		minz = std::min<float>( minz, z );
		maxx = std::max<float>( maxx, x );
		maxy = std::max<float>( maxy, y );
		maxz = std::max<float>( maxz, z );
	}

	Vector3d min(minx, miny, minz);
	Vector3d max(maxx, maxy, maxz);
	return Box(min, max);
}
