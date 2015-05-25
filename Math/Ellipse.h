#ifndef __CRYSTAL_MATH_ELLIPSE_H__
#define __CRYSTAL_MATH_ELLIPSE_H__

#include "Tolerance.h"

#include "Vector2d.h"

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

	T getXRadius() const { return radii.getX(); }

	T getYRadius() const { return radii.getY(); }

	//T getOblateness() const { return }

	T getMajor() const { return std::max<T>( radii.getX(), radii.getY() ); }

	T getMinor() const { return std::min<T>( radii.getX(), radii.getY() ); }

	Vector2d<float> getRadii() const { return radii; }

	T getArea() const { return Tolerancef::getPI() * getXRadius() * getYRadius(); }

	bool isCircle() const { return Tolerancef::isEqualStrictly(radii.getX(), radii.getY()); }

	bool isShrinked() const { return Tolerancef::isEqualStrictly(getArea(), 0.0); }

private:
	Vector2d<T> radii;
};

	}
}

#endif