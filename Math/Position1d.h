#ifndef __CRSYTAL_MATH_POSITION_1D_H__
#define __CRSYTAL_MATH_POSITION_1D_H__

#include <cmath>
#include <vector>
#include <array>
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

	Position1d& move(const T& rhs) {
		v += rhs;
		return *(this);
	}

	Position1d& operator+=(const T& rhs) {
		return move(rhs);
	}

	Position1d operator+(const T& rhs) const {
		return Position1d(v + rhs);
	}

	Position1d& operator-=(const T& rhs) {
		v -= rhs;
		return (*this);
	}

	Position1d operator-(const T& rhs) const {
		return Position1d(v - rhs);
	}

	bool equals(const Position1d<T>&rhs) const {
		return Tolerance<T>::isEqualLoosely(v,rhs.v);
	}

	bool operator==(const Position1d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Position1d<T>& rhs) const {
		return !equals(rhs);
	}

	bool operator<(const Position1d<T>& rhs) const {
		return v < rhs.v;
	}

	bool operator>(const Position1d<T>& rhs) const {
		return v > rhs.v;
	}


	T get() const { return v; }

private:
	T v;
};

template<typename T>
using Position1dVector = std::vector < Position1d<T> > ;

	}
}

#endif