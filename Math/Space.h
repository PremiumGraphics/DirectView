#ifndef __CRYSTAL_MATH_SPACE_H__
#define __CRYSTAL_MATH_SPACE_H__

#include "Vector.h"
#include "Position.h"

namespace Crystal {
	namespace Math {

template< typename T, size_t DIM >
class Space final {
public:
	Space() = default;

	Space(const Position<T,DIM>& start, const Vector<T,DIM>& length) :
		origin(start),
		vector(length)
	{}

	Position<T,DIM> getStart() const { return origin; }

	T getEnd() const { return origin.get(0) + vector.get(0); }

	//Vector<T,DIM> getVector() const { return vector; }

	/*
	bool hasIntersection(const Space1d<N,T>& rhs) {
		const auto& line1 = getBoundingLine();
		const auto& line2 = rhs.getBoundingLine();
		return line1.hasInersection(line2);
	}
	*/

	/*
	unsigned float getDiff( const Space1d& rhs) const {
		return start.get() - rhs.getStart();
	}
	*/

private:
	Position<T,DIM> origin;
	Vector<T,DIM> vector;
};

	}
}

#endif