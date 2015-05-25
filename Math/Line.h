#ifndef __CRYSTAL_MATH_LINE_H__
#define __CRYSTAL_MATH_LINE_H__

#include "Position.h"
#include "Vector.h"

#include <cassert>

namespace Crystal {
	namespace Math {

template< typename T, size_t DIM >
class Line final
{
public:
	Line()
	{
		for (size_t i = 0; i < DIM; ++i)  {
			start.set(i, 0);
		}

	}

	~Line() = default;

	Line(const Position<T,DIM>& start) :
		start(start)
	{}


	Line(const Position<T,DIM>& start, const Vector<T,DIM>& vector) :
		start(start),
		vector(vector)
	{}

	Line(const Position<T,DIM>& start, const Position<T,DIM>& end) :
		start( start)
	{
		for (size_t i = 0; i < DIM; ++i)  {
			vector.set(i, end.get_(i) - start.get_(i));
		}
	}

	Position<T,DIM> getStart() const { return start; }

	T getLength() const { return vector.getLength(); }

	Position<T,DIM> getEnd() const {
		Position<T,DIM> end;
		for (size_t i = 0; i < DIM; ++i) {
			end.set(i, start.get_(i) + vector.get_(i));
		}
		return end;
	}

	//Position<T,DIM> getCenter() const { return start + length * T(0.5); }

	bool equals(const Line& rhs) const {
		return 
			start == rhs.start &&
			length == rhs.length;
	}

	bool operator==(const Line& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Line& rhs) const {
		return !equals(rhs);
	}

	/*
	T getLength(const Line1d<T>& rhs) const {
		return ::fabs( getEnd() - rhs.getStart() );
	}
	*/

private:
	Position<T, DIM> start;
	Vector<T,DIM> vector;
};

template<typename T>
using Line1d = Line < T, 1 > ;
template<typename T>
using Line2d = Line < T, 2 > ;
template<typename T>
using Line3d = Line < T, 3 >;

	}
}

#endif