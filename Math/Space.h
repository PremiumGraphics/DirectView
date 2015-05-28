#ifndef __CRYSTAL_MATH_SPACE_H__
#define __CRYSTAL_MATH_SPACE_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template< typename T >
class Space3d final {
public:
	Space3d() = default;

	explicit Space3d(const Vector3d<T>& origin) :
		origin(origin)
	{}

	Space3d(const Vector3d<T>& origin, const Vector3d<T>& length) :
		origin(origin),
		vector(length)
	{}

	Vector3d<T> getStart() const { return origin; }

	Vector3d<T> getVector() const { return vector; }

	Vector3d<T> getEnd() const { return origin + vector; }

	Vector3d<T> getCenter() const { origin + vector * 0.5; }

	bool equals(const Space3d& rhs) const {
		return
			getStart() == rhs.getStart() &&
			getVector() == rhs.getVector();
	}

	bool operator==(const Space3d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Space3d& rhs) const {
		return !equals(rhs);
	}

	std::vector< Space3d<T> > getDivided(const T xdiv, const T ydiv, const T zdiv) const  {
		assert(xdiv >= 1 && ydiv >= 1 && zdiv >= 1);

		const auto lengthx = vector.getX() / xdiv;
		const auto lengthy = vector.getY() / ydiv;
		const auto lengthz = vector.getZ() / zdiv;
		const Vector3d<T> l(lengthx, lengthy, lengthz);

		std::vector< Space3d<T> > spaces;
		for (size_t i = 0; i < xdiv; ++i) {
			for (size_t j = 0; j < ydiv; ++j) {
				for (size_t k = 0; k < zdiv; ++k) {
					//Vector3d<T> origin = origin + l * i ;
					const auto originx = origin.getX() + lengthx * i;
					const auto originy = origin.getY() + lengthy * j;
					const auto originz = origin.getZ() + lengthz * k;
					const Vector3d<T> origin_(originx, originy, originz);
					spaces.push_back( Space3d<T>(origin_, l) );
				}
			}
		}
		return spaces;
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
	Vector3d<T> origin;
	Vector3d<T> vector;
};

	}
}

#endif