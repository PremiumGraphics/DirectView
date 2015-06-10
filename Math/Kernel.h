#ifndef __CRYSTAL_MATH_KERNEL_H__
#define __CRYSTAL_MATH_KERNEL_H__

#include <memory>
#include <list>
#include "Vector.h"
#include "Tolerance.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Gaussian {
public:
	Gaussian() :
		average(0),
		distribution(1)
	{}

	Gaussian(const T average, const T distribution) :
		average( average ),
		distribution( distribution )
	{}

	~Gaussian() = default;

	T get(const T x) {
		const auto coe = T(1) / std::sqrt(T(2) * Tolerance<T>::getPI() * distribution * distribution);
		const auto exp_ = -std::pow((x - average), 2) / (T(2) * distribution);
		return coe * std::exp(exp_);
	}

	T get(const T x, const T y){
		return get(x) + get(y);
	}

	T get(const T x, const T y, const T z) {
		return get(x) + get(y) + get(z);
	}

private:
	T average;
	T distribution;
};

template<typename T>
class Metaball {
public:
	Metaball() :
		radius(1)
	{}

	Metaball(const Vector3d<T>& center, const T radius) :
		center( center ),
		radius( radius )
	{}


	T getRadius() const { return radius; }

	Vector3d<T> getCenter() const { return center; }

	T getValue(const Math::Vector3d<T>& pos) const
	{
		const auto dist = pos.getDistance(center);
		const auto v = 1.0f - dist / radius;
		return v;
	}

private:
	Vector3d<float> center;
	T radius;
};

template<typename T>
using MetaballSPtr = std::shared_ptr < Metaball<T> > ;

template<typename T>
using MetaballSPtrList = std::list < MetaballSPtr<T> > ;

	}
}

#endif