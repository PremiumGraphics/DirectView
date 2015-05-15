#ifndef __CRYSTAL_MATH_LINE_3D_H__
#define __CRYSTAL_MATH_LINE_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Line3d
{
public:
	Line3d() :
		start(Vector3d( 0.0f, 0.0f, 0.0f)),
		end(Vector3d(1.0f, 0.0f, 0.0f))
	{}

	Vector3d getStart() const { return start; }

	Vector3d getEnd() const { return end; }

	T getLength() const { return start.getDistanceSquared(end); }

private:
	Vector3d start;
	Vector3d end;
};

	}
}

#endif