#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "Polygon.h"

#include "FaceBuilder.h"

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:

	PolygonBuilder() :
		nextId(0)
	{}

	Polygon* buildQuad();

	Polygon* buildBox();

	Polygon* buildCircleByNumber(const float radius, const unsigned int divideNumber);

	Polygon* buildCircleByAngle(const float radius, const float divideAngle);

	Polygon* buildTriangle() { return buildCircleByNumber(1.0f, 3); }

	Polygon* buildCylinder(const unsigned int divideNuber);

	Polygon* buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	Polygon* buildCone(const unsigned int divideNumber);


private:
	unsigned int nextId;

	FaceBuilder faceBuilder;
};
	}
}

#endif