#ifndef __CRSYTAL_MATH_POSITION_1D_H__
#define __CRSYTAL_MATH_POSITION_1D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

#include "Position1d.h"

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
		return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
	}

	bool operator==(const Position1d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Position1d<T>& rhs) const {
		return !equals(rhs);
	}

private:
	T v;
};

	}
}

#endif