#ifndef __CRYSTAL_MATH_LINE_3D_H__
#define __CRYSTAL_MATH_LINE_3D_H__

#include "Vector3d.h"
#include "Position3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Line3d
{
public:
	Line3d() :
		start(Position3d<T>( 0.0f, 0.0f, 0.0f)),
		vector(Vector3d_<T>(1.0f, 0.0f, 0.0f))
	{}

	Position3d<T> getStart() const { return start; }

	Position3d<T> getEnd() const {
		const auto x = start.getX() + vector.getX();
		const auto y = start.getY() + vector.getY();
		const auto z = start.getZ() + vector.getZ();
		return Position3d<T>(x,y,z);
	}

	T getLength() const { return vector.getLength(); }

private:
	Position3d<T> start;
	Vector3d_<T> vector;
};

	}
}

#endif