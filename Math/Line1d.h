#ifndef __CRYSTAL_MATH_LINE_1D_H__
#define __CRYSTAL_MATH_LINE_1D_H__

#include "Vector1d.h"

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

	Line1d(const T start, const T length) :
		start(start),
		length(length)
	{}


	/*
	Line1d(const Position1d<T>& start, const Position1d<T>& end) :
		start(start),
		length(end - start)
	{}
	*/

	T getStart() const { return start; }

	T getLength() const { return length; }

	T getEnd() const { return start + length; }

	Line1d& move(const T v) {
		start += v;
		return (*this);
	}

	void sacle(const T s) { length *= s; }

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

	/*
	bool hasIntersection(const Line1d<T>& rhs) const {
		return
			const auto diff = Vector1d<T>(start, rhs.start()).getLength();
			
	}
	*/


private:
	T start;
	T length;
};
	}
}

#endif