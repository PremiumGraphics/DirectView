#ifndef __CRYSTAL_MATH_LINE_1D_H__
#define __CRYSTAL_MATH_LINE_1D_H__

#include "Position1d.h"

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

	explicit Line1d(const Position1d<T>& start, const Position1d<T>& end) :
		start(start),
		length(end.get()-start.get())
	{}


	explicit Line1d(const std::array<Position1d<T>, 2>& positions) :
		start(positions[0]),
		end( positions[1] - positions[0])
	{
	}

	Line1d(const T start, const T length) :
		start(start),
		length(length)
	{}


	Position1d<T> getStart() const { return start; }

	T getLength() const { return length; }

	Position1d<T> getEnd() const { return start + length; }

	Line1d& move(const T v) {
		start += v;
		return (*this);
	}

	Line1d move(const T& v) const {
		return Line1d( start.get() + v, length );
	}

	Line1d& sacle(const T s) {
		length *= s;
		return (*this);
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

	bool hasIntersection(const Line1d<T>& rhs) const {
		if (getEnd() < rhs.getStart() || getStart() > rhs.getEnd()) {
			return false;
			//return rhs.hasIntersection( *this );
		}
		/*
		if (start < rhs.start) {
			return getEnd() < rhs.getEnd();
		}
		else {
			return getEnd() > rhs.getEnd();

		}
		*/
		const auto diff = start.get() - rhs.start.get();//Vector1d<T>(start, rhs.start()).getLength();
		const auto moved = rhs.move(diff);
		return moved.getEnd() < rhs.getEnd();
	}

private:
	Position1d<T> start;
	T length;
};
	}
}

#endif