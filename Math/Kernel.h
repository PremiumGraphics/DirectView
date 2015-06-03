#ifndef __CRYSTAL_MATH_KERNEL_H__
#define __CRYSTAL_MATH_KERNEL_H__

#include <math.h>
#include "Tolerance.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Gaussian1d {
public:
	Gaussian1d() :
		average(0),
		distribution(1)
	{}

	Gaussian1d(const T average, const T distribution) :
		average( average ),
		distribution( distribution )
	{}

	~Gaussian1d() = default;

	T get(const T x) {
		const auto coe = 1.0 / std::sqrt(2.0 * Tolerance<T>::getPI() * distribution * distribution);
		const auto exp_ = -std::pow((x - average), 2) / (2.0 * distribution);
		return coe * std::exp(exp_);
	}

private:
	T average;
	T distribution;
};

	}
}

#endif