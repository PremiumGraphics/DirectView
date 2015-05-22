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
	Triangle() :
		v0(Position3d<T>(0.0, 0.0, 0.0)),
		v1(Position3d<T>(1.0, 0.0, 0.0)),
		v2(Position3d<T>(0.0, 1.0, 0.0))
	{}

	Triangle( const Position3d<T>& v0, const Position3d<T>& v1, const Position3d<T>& v2) :
		v0( v0 ),
		v1( v1 ),
		v2( v2 )
	{
	}

	static Triangle<T> UnitXY() {
		return Triangle<T>(
			Position3d<T>(0.0, 0.0, 0.0),
			Position3d<T>(1.0, 0.0, 0.0),
			Position3d<T>(0.0, 1.0, 0.0)
		);
	}

	static Triangle<T> UnitXZ() {
		return Triangle<T>(
			Position3d<T>(0.0, 0.0, 0.0),
			Position3d<T>(0.0, 0.0, 1.0),
			Position3d<T>(1.0, 0.0, 0.0)
			);
	}

	static Triangle<T> UnitYZ() {
		return Triangle<T>(
			Position3d<T>(0.0, 0.0, 0.0),
			Position3d<T>(0.0, 1.0, 0.0),
			Position3d<T>(0.0, 0.0, 1.0)
			);
	}


	Vector3d_<T> getNormal() const {
		const Vector3d_<T> v01 = v0.diff(v1);
		const Vector3d_<T> v02 = v1.diff(v2);
		return v01.getOuterProduct(v02).getNormalized();
	}

	T getArea() const {
		const Vector3d_<T> v01 = v0.diff(v1);
		const Vector3d_<T> v02 = v1.diff(v2);
		return v01.getOuterProduct(v02).getLength() * T(0.5);
	}

	bool isCCW() const {
		assert( isValid() );
		return getNormal().getLength() >= 0.0f;
	}

	bool isCW() const {
		assert( isValid() );
		return !isCCW();
	}

	Vector3d_<T> getCenter() const {
		return (v0 + v1 + v2) / T(3);
	}

	bool isValid() const {
		return ( v0 != v1 ) && ( v1 != v2 ) && ( v0 != v2 );
	}

	/*
	bool isShrinekd() const {
		return Tolerance<T>::isEqualLoosely( get)
	}
	*/

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