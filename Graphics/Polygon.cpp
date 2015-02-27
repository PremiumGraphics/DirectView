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

Polygon* Polygon::createTriangle()
{
	return createCricleByNumber(1.0f,3);
}


Polygon* Polygon::createCricleByNumber(const float radius, const unsigned int divideNumber)
{
	Polygon* p = new Polygon();
	Vector3dVector positions;
	Vector3dVector normals;
	std::vector<unsigned int> vertexIds;
	Face f;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0 / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		normals.push_back(Vector3d(0.0, 0.0, 1.0));
		vertexIds.push_back(i);
	}
	f.setVertexIds(vertexIds);
	f.setNormalIds(vertexIds);
	p->setPositions(positions);
	p->setNormals(normals);
	p->faces = { f };
	return p;
}

Polygon* Polygon::createCircleByAngle( const float radius, const float divideAngle)
{
	const unsigned int number = 360.0 / divideAngle;
	return createCricleByNumber( radius, number);
}

Polygon* Polygon::createCylinder(const float radius, const float height)
{
	Graphics::Polygon* p = new Graphics::Polygon();

	Vector3dVector positions;
	Vector3dVector normals;
	Face f;
	std::vector<unsigned int > vertexIds;
	int i = 0;
	for (float angle = 0.0; angle < 360.0; angle += 60.0) {
		const float rad = angle * Tolerances::getPI() / 180.0f;
		positions.push_back(Vector3d(std::sin(rad) * radius, std::cos(rad) * radius, 0.0f));
		normals.push_back(Vector3d(0.0, -1.0, 0.0));
		vertexIds.push_back(i++);
	}
	f.setVertexIds(vertexIds);

	vertexIds.clear();
	Face f1;
	for (float angle = 0.0; angle < 360.0; angle += 60.0) {
		const float rad = angle * Tolerances::getPI() / 180.0f;
		positions.push_back(Vector3d(std::sin(rad) * radius, std::cos(rad) * radius, height));
		normals.push_back(Vector3d(0.0, 1.0, 0.0));
		vertexIds.push_back(i++);
	}
	f1.setVertexIds(vertexIds);

	assert(f.getVertexIds().size() == f1.getVertexIds().size());
	vertexIds.clear();

	Face f3;
	for (size_t i = 0; i < f.getVertexIds().size() - 1; ++i) {
		std::vector<unsigned int> vids = { f.getVertexIds()[i], f.getVertexIds()[i + 1], f1.getVertexIds()[i] };
		f3.setVertexIds(vids);
	}

	p->setPositions(positions);
	p->setNormals(normals);

	p->faces = std::vector < Face > {f, f1, f3};
	return p;
}