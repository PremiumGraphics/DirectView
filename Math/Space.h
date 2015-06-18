#ifndef __CRYSTAL_MATH_SPACE_H__
#define __CRYSTAL_MATH_SPACE_H__

#include "Vector.h"
#include <array>

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

	~Space3d() = default;

	static Space3d<T> Unit() {
		return Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	}

	Vector3d<T> getStart() const { return origin; }

	Vector3d<T> getLengths() const { return vector; }

	T getVolume() const { return vector.getX() * vector.getY() * vector.getZ(); }

	Vector3d<T> getEnd() const { return origin + vector; }

	Vector3d<T> getCenter() const { return origin + vector * 0.5; }

	void scale(const Vector3d<T>& v)  {
		vector.scale( v.getX(), v.getY(), v.getZ() );
	}

	Space3d moveStart(const Vector3d<T>& v) const {
		return Vector3d<T>(origin + v, vector - v);
	}

	Space3d& moveStart(const Vector3d<T>& v) {
		origin += v;
		vector -= v;
		return (*this);
	}

	Space3d moveEnd(const Vector3d<T>& v) const {
		return Vector3d<T>(origin, vector + v);
	}

	Space3d& moveEnd(const Vector3d<T>& v) {
		vector += v;
		return (*this);
	}

	Space3d& move(const Vector3d<T>& v) {
		moveStart(v);
		moveEnd(v);
		return (*this);
	}

	bool equals(const Space3d& rhs) const {
		return
			getStart() == rhs.getStart() &&
			getLengths() == rhs.getLengths();
	}

	bool operator==(const Space3d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Space3d& rhs) const {
		return !equals(rhs);
	}

	std::vector< Space3d<T> > getDivided(const unsigned int xdiv, const unsigned int ydiv, const unsigned int zdiv) const  {
		assert(xdiv >= 1 && ydiv >= 1 && zdiv >= 1);

		const auto lengthx = vector.getX() / xdiv;
		const auto lengthy = vector.getY() / ydiv;
		const auto lengthz = vector.getZ() / zdiv;
		const Vector3d<T> l(lengthx, lengthy, lengthz);

		std::vector< Space3d<T> >spaces;
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

	std::array< Vector3d<T>, 8 > toArray() const {
		const auto x1 = getStart().getX();
		const auto y1 = getStart().getY();
		const auto z1 = getStart().getZ();
		const auto x2 = getEnd().getX();
		const auto y2 = getEnd().getY();
		const auto z2 = getEnd().getZ();

		return{
			Vector3d<T>(x1, y1, z1),
			Vector3d<T>(x2, y1, z1),
			Vector3d<T>(x2, y2, z1),
			Vector3d<T>(x1, y2, z1),
			Vector3d<T>(x1, y1, z2),
			Vector3d<T>(x2, y1, z2),
			Vector3d<T>(x2, y2, z2),
			Vector3d<T>(x1, y2, z2),
		};
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


	bool hasIntersection(const Space3d& rhs) const {
		const auto distx = std::fabs(getCenter().getX() - rhs.getCenter().getX());
		const auto lx = getLengths().getX() * 0.5 + rhs.getLengths().getX() * 0.5;

		const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
		const auto ly = getLengths().getY() * 0.5 + rhs.getLengths().getY() * 0.5;

		const auto distz = std::fabs(getCenter().getZ() - rhs.getCenter().getZ());
		const auto lz = getLengths().getZ() * 0.5 + rhs.getLengths().getZ() * 0.5;

		return (distx < lx && disty < ly && distz < lz);
	}


	Space3d getOverlapped(const Space3d& rhs) const {
		if (!hasIntersection(rhs)) {
			return Space3d();
		}
		const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
		const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());
		const auto minz = std::max<T>(this->getStart().getZ(), rhs.getStart().getZ());

		const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
		const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());
		const auto maxz = std::min<T>(this->getEnd().getZ(), rhs.getEnd().getZ());

		const Vector3d<T> min_(minx, miny, minz);
		const Vector3d<T> max_(maxx, maxy, maxz);
		return Space3d(min_, max_ - min_);
	}

	Space3d<T> offset(const Vector3d<T>& v) const {
		return Space3d<T>(origin + v * 0.5, vector - v);
	}


private:
	Vector3d<T> origin;
	Vector3d<T> vector;
};


	}
}

#endif