#include "Polygon.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Polygon* Polygon::createTriangle()
{
	Graphics::Polygon* p = new Graphics::Polygon();
	p->name = "triangle";
	p->setPositions({
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	});
	p->setNormals({
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	});
	//	p->normals = {};
	Face f;
	f.setVertexIds({ 0, 1, 2 });
	p->faces = std::vector < Face > {f};
	return p;
}

Polygon* Polygon::createQuad()
{
	Graphics::Polygon* p = new Graphics::Polygon();
	p->name = "quad";
	p->setPositions({
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0),
		Vector3d(0.0, 1.0, 0.0)
	});
	p->setNormals({
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	});
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	p->faces = std::vector < Face > {f};
	return p;
}

Polygon* Polygon::createCircle( const float radius, const float divideAngle)
{
	Graphics::Polygon* p = new Graphics::Polygon();
	p->name = "circle";
	VectorVector positions;
	VectorVector normals;
	Face f;
	int i = 0;
	std::vector<unsigned int> vertexIds;
	for (float angle = 0.0; angle < 360.0; angle += divideAngle) {
		const float rad = angle * Tolerances::getPI() / 180.0f;
		positions.push_back( radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		normals.push_back(Vector3d(0.0, 0.0, 1.0));
		vertexIds.push_back(i++);
	}
	f.setVertexIds(vertexIds);
	p->setPositions(positions);
	p->setNormals(normals);

	p->faces = std::vector < Face > {f};
	return p;
}

Polygon* Polygon::createCylinder()
{
	Graphics::Polygon* p = new Graphics::Polygon();
	p->name = "cylinder";
	VectorVector positions;
	VectorVector normals;
	Face f;
	std::vector<unsigned int > vertexIds;
	int i = 0;
	for (float angle = 0.0; angle < 360.0; angle += 60.0) {
		const float rad = angle * Tolerances::getPI() / 180.0f;
		positions.push_back(Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		normals.push_back(Vector3d(0.0, 0.0, 1.0));
		vertexIds.push_back(i++);
	}
	f.setVertexIds(vertexIds);

	vertexIds.clear();
	Face f1;
	for (float angle = 0.0; angle < 360.0; angle += 60.0) {
		const float rad = angle * Tolerances::getPI() / 180.0f;
		positions.push_back(Vector3d(std::sin(rad), std::cos(rad), 1.0f));
		normals.push_back(Vector3d(0.0, 0.0, 1.0));
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