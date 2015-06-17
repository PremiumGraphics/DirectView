#ifndef __CRYSTAL_MATH_LINE_H__
#define __CRYSTAL_MATH_LINE_H__

#include "Vector.h"

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Line3d final
{
public:
	Line3d(const Vector3d<T>& start, const Vector3d<T>& end) :
		start( start ),
		vector( end - start )
	{
	}

	Vector3d<T> getStart() const { return start; }

	Vector3d<T> getCenter() const { return start + vector * T(0.5); }

	Vector3d<T> getEnd() const { return start + vector; }

private:
	Vector3d<T> start;
	Vector3d<T> vector;
};

template<typename T>
using Line3dVector = std::vector < Line3d<T> > ;
	}
}

#endif