#ifndef __CRYSTAL_MATH_TRIANGLE_H__
#define __CRYSTAL_MATH_TRIANGLE_H__

#include <vector>
#include <cassert>

#include "Position3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Triangle final
{
public:
	Triangle()
	{}

	Triangle( const Position3d<T>& v0, const Position3d<T>& v1, const Position3d<T>& v2) :
		v0( v0 ),
		v1( v1 ),
		v2( v2 )
	{
	}

	/*
	Vector3d getNormal() const {
		const Vector3d v01(v0, v1);
		const Vector3d v02(v0, v2);
		return v01.getOuterProduct(v02).getNormalized();
	}

	bool isCCW() const {
		assert( isValid() );
		return getNormal().getLength() >= 0.0f;
	}

	bool isCW() const {
		assert( isValid() );
		return !isCCW();
	}

	Vector3d getCenter() const {
		return (v0 + v1 + v2) / 3.0f;
	}
	*/

	bool isValid() const {
		return ( v0 != v1 ) && ( v1 != v2 ) && ( v0 != v2 );
	}

	Position3d<T> getv0() const { return v0; }

	Position3d<T> getv1() const { return v1; }

	Position3d<T> getv2() const { return v2; }

	void setv0( const Position3d<T>& v ) { this->v0 = v; }

	void setv1( const Position3d<T>& v ) { this->v1 = v; }

	void setv2( const Position3d<T>& v ) { this->v2 = v; }

private:
	Position3d<T> v0;
	Position3d<T> v1;
	Position3d<T> v2;

};

template<typename T>
using TriangleVector = std::vector< Triangle<T> >;

	}
}

#endif