#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "../Graphics/Polygon.h"

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:

	static Polygon* buildQuad();

	static Polygon* buildBox();

	static Polygon* buildCircleByNumber(const float radius, const unsigned int divideNumber);

	static Polygon* buildCircleByAngle(const float radius, const float divideAngle);

	static Polygon* buildTriangle() { return buildCircleByNumber(1.0f, 3); }

	static Polygon* buildCylinder(const unsigned int divideNuber);

	static Polygon* buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	static Polygon* buildCone(const unsigned int divideNumber);

};
	}
}

#endif