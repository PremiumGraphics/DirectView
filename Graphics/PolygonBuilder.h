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

	void create() {
		Polygon* polygon = new Polygon();
		polygon->setPositions(positions);
		polygon->setNormals(normals);
		polygon->setFaces(faces);
		this->polygon = polygon;
	};

	Polygon* getPolygon() {
		create();
		return polygon;
	}

private:
	Polygon* polygon;
	Math::Vector3dVector positions;
	Math::Vector3dVector normals;
	FaceVector faces;
};
	}
}

#endif