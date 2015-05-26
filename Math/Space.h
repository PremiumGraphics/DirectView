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

	Space(const Position<T, DIM>& origin) :
		origin(origin)
	{}

	Space(const Position<T,DIM>& origin, const Vector<T,DIM>& length) :
		origin(origin),
		vector(length)
	{}

	Position<T,DIM> getStart() const { return origin; }

	Vector<T, DIM> getVector() const { return vector; }

	Position<T,DIM> getEnd() const {
		std::array<T, DIM> vs;
		for (size_t i = 0; i < DIM; ++i) {
			vs[i] = origin.get(i) + vector.get(i);
		}
		return Position<T,DIM>(vs);
	}

	Position<T,DIM> getCenter() const {
		std::array<T, DIM> vs;
		for (size_t i = 0; i < DIM; ++i) {
			vs[i] = origin.get(i) + vector.get(i) / T(2);
			p.set(i, x);
		}
		return Position<T, DIM>(vs);
	}

	bool equals(const Space& rhs) const {
		return
			getStart() == rhs.getStart() &&
			getVector() == rhs.getVector();
	}

	bool operator==(const Space& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Space& rhs) const {
		return !equals(rhs);
	}



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