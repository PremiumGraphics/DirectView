#ifndef __CRYSTAL_MATH_ELLIPSE_H__
#define __CRYSTAL_MATH_ELLIPSE_H__

#include "Tolerance.h"

#include "Vector.h"

#include <algorithm>

namespace Crystal {
	namespace Math {

template<typename T>
class Ellipse final
{
public:
	Ellipse() : Ellipse(Vector2d<T>({ 1.0f, 1.0f }))
	{}

	explicit Ellipse(const T x, const T y) : Ellipse(Vector2d<T>({ x, y }))
	{}

	Ellipse(const Vector2d<T> radii) :
		radii( radii )
	{}

	T getXRadius() const { return radii.get<0>(); }

	T getYRadius() const { return radii.get_(1); }

	//T getOblateness() const { return }

	T getMajor() const { return std::max<T>( radii.get<0>(), radii.get_(1) ); }

	T getMinor() const { return std::min<T>( radii.get<0>(), radii.get_(1) ); }

	Vector2d<float> getRadii() const { return radii; }

	T getArea() const { return Tolerancef::getPI() * getXRadius() * getYRadius(); }

	bool isCircle() const { return Tolerancef::isEqualStrictly(radii.get<0>(), radii.get_(1)); }

	bool isShrinked() const { return Tolerancef::isEqualStrictly(getArea(), 0.0); }

private:
	Vector2d<T> radii;
};

	}
}

#endif