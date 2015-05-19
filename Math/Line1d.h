#ifndef __CRYSTAL_MATH_LINE_1D_H__
#define __CRYSTAL_MATH_LINE_1D_H__

#include "Position1d.h"

#include <cassert>

namespace Crystal {
	namespace Math {

template< typename T >
class Line1d final
{
public:
	Line1d() :
		start(0.0f),
		length(1.0f)
	{}

	~Line1d() = default;

	explicit Line1d(const T start) :
		start(start),
		length(1.0f)
	{}

	Line1d(const Position1d<T>& start, const T length) :
		start(start),
		length(length)
	{}

	Line1d(const Position1d<T>& start, const Position1d<T>& end) :
		start(start),
		length(end.get()-start.get())
	{}

	Line1d(const T start, const T length) :
		start(start),
		length(length)
	{}


	Position1d<T> getStart() const { return start; }

	T getLength() const { return length; }

	Position1d<T> getEnd() const { return start + length; }

	Position1d<T> getCenter() const { return start + length * T(0.5); }

	Line1d& move(const T v) {
		start += v;
		return (*this);
	}

	Line1d move(const T& v) const {
		return Line1d( start.get() + v, length );
	}

	Line1d& scale(const T s) const {
		length *= s;
		return (*this);
	}

	Line1d scale(const T s) {
		return Line1d( getStart(), length * s);
	}


	bool equals(const Line1d<T>& rhs) const {
		return 
			start == rhs.start &&
			length == rhs.length;
	}

	bool operator==(const Line1d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Line1d<T>& rhs) const {
		return !equals(rhs);
	}

	T getLength(const Line1d<T>& rhs) const {
		return ::fabs( getEnd() - rhs.getStart() );
	}

	bool hasIntersection(const Line1d<T>& rhs) const {
		const auto dist = getCenter().getDistance(rhs.getCenter());
		return ( dist <  getLength() * T(0.5) + rhs.getLength() * T(0.5) );
	}

	Line1d<T> getOverlapped(const Line1d<T>& rhs) const {
		assert(hasIntersection(rhs));
		const auto min = std::max<T>( this->getStart().get(), rhs.getStart().get());
		const auto max = std::min<T>( this->getEnd().get(), rhs.getEnd().get() );
		return Line1d( Position1d<T>( min ), Position1d<T>( max) );
	}

private:
	Position1d<T> start;
	T length;
};
	}
}

#endif