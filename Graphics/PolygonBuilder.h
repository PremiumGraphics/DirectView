#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "../Graphics/Polygon.h"

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:
	PolygonBuilder() :
		polygon(nullptr)
	{}

	void buildQuad();

	void buildBox();

	void buildCircleByNumber(const float radius, const unsigned int divideNumber);

	void buildCircleByAngle(const float radius, const float divideAngle);

	void buildTriangle() { buildCircleByNumber(1.0f, 3); }

	void buildCylinder(const unsigned int divideNuber);

	void buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	void buildCone(const unsigned int divideNumber);

	void create() {
		Polygon* polygon = new Polygon();
		polygon->setVertices(vertices);
		polygon->setNormals(normals);
		polygon->setFaces(faces);
		polygon->setEdges(edges);
		this->polygon = polygon;
	};

	Polygon* getPolygon() {
		create();
		return polygon;
	}

private:
	Polygon* polygon;
	VertexVector vertices;
	Math::Vector3dVector normals;
	HalfEdgeList edges;
	FaceVector faces;
};
	}
}

#endif