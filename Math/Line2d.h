#ifndef __CRYSTAL_MATH_LINE_2D_H__
#define __CRYSTAL_MATH_LINE_2D_H__

#include "Position.h"
#include "Vector.h"

#include <cassert>

namespace Crystal {
	namespace Math {

template< typename T >
class Line2d final
{
public:
	Line2d()
	{}

	~Line2d() = default;

	Line2d(const Position2d<T>& start) :
		start(start)
	{}


	Line2d(const Position2d<T>& start, const Vector2d<T>& vector) :
		start(start),
		vector(vector)
	{}

	Line2d(const Position2d<T>& start, const Position2d<T>& end) :
		start( start)
	{
		vector = Vector2d<T>({ end.getX() - start.getX(), end.getY() - start.getY() });
	}

	Position2d<T> getStart() const { return start; }

	T getLength() const { return vector.getLength(); }

	Position2d<T> getEnd() const { return start + vector; }

	/*
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
	*/

	bool equals(const Line2d<T>& rhs) const {
		return 
			start == rhs.start &&
			length == rhs.length;
	}

	bool operator==(const Line2d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Line2d<T>& rhs) const {
		return !equals(rhs);
	}

	/*
	T getLength(const Line1d<T>& rhs) const {
		return ::fabs( getEnd() - rhs.getStart() );
	}
	*/

private:
	Position2d<T> start;
	Vector2d<T> vector;
};
	}
}

#endif