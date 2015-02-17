#ifndef __CRYSTAL_MATH_TRIANGLE_H__
#define __CRYSTAL_MATH_TRIANGLE_H__

#include <vector>
#include <cassert>

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Triangle
{
public:
	Triangle()
	{}

	Triangle( const Vector3d& v0, const Vector3d& v1, const Vector3d& v2) :
		v0( v0 ),
		v1( v1 ),
		v2( v2 )
	{
	}

	Vector3d getNormal() const;

	bool isCCW() const {
		assert( isValid() );
		return getNormal().getLength() >= 0.0f;
	}

	bool isCW() const {
		assert( isValid() );
		return !isCCW();
	}

	Vector3d getCenter() const;

	bool isValid() const {
		return ( v0 != v1 ) && ( v1 != v2 ) && ( v0 != v2 );
	}

	Vector3d getv0() const { return v0; }

	Vector3d getv1() const { return v1; }

	Vector3d getv2() const { return v2; }

	void setv0( const Vector3d& v ) { this->v0 = v; }

	void setv1( const Vector3d& v ) { this->v1 = v; }

	void setv2( const Vector3d& v ) { this->v2 = v; }

private:
	Vector3d v0;
	Vector3d v1;
	Vector3d v2;

};

typedef std::vector< Triangle > TriangleVector;

	}
}

#endif