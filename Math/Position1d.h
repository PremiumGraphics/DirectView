#ifndef __CRSYTAL_MATH_POSITION_1D_H__
#define __CRSYTAL_MATH_POSITION_1D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

namespace Crystal{
	namespace Math{

template< typename T >
class Position1d final
{
public:

	Position1d(void)
	{}

	explicit Position1d(const T v) :
		v(v)
	{}

	T getDistance(const Position1d<T>& rhs) const {
		return ::fabs(rhs.v - v);
	}

	/*
	T getDistanceSquared(const Position1d<T>& rhs) const {
		return std::pow()
	}
	*/

	bool equals(const Position1d<T>&rhs) const {
		return Tolerance<T>::isEqualLoosely(v,rhs.v);
	}

	bool operator==(const Position1d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Position1d<T>& rhs) const {
		return !equals(rhs);
	}

	T get() const { return v; }

private:
	T v;
};

	}
}

#endif