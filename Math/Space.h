#ifndef __CRYSTAL_MATH_SPACE_H__
#define __CRYSTAL_MATH_SPACE_H__

#include "Vector.h"
#include "Bitmap.h"
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

	Vector3d<T> getStart() const { return origin; }

	Vector3d<T> getVector() const { return vector; }

	Vector3d<T> getEnd() const { return origin + vector; }

	Vector3d<T> getCenter() const { return origin + vector * 0.5; }

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
		const auto lx = getVector().getX() * 0.5 + rhs.getVector().getX() * 0.5;

		const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
		const auto ly = getVector().getY() * 0.5 + rhs.getVector().getY() * 0.5;

		const auto distz = std::fabs(getCenter().getZ() - rhs.getCenter().getZ());
		const auto lz = getVector().getZ() * 0.5 + rhs.getVector().getZ() * 0.5;

		return (distx < lx && disty < ly && distz < lz);
	}


private:
	Vector3d<T> origin;
	Vector3d<T> vector;
};

template< typename T >
class BitSpace3d final {
public:
	BitSpace3d() = default;

	BitSpace3d(const Space3d<T>& space, const Bitmap3d& bmp) :
		space( space ),
		bmp( bmp )
	{}

	/*
	BitSpace3d getIntersection() const {
	}
	*/

	Vector3d<T> getUnitLength() const {
		const auto x = space.getVector().getX() / bmp.getSizeX();
		const auto y = space.getVector().getY() / bmp.getSizeY();
		const auto z = space.getVector().getZ() / bmp.getSizeZ();
		return Vector3d<T>(x, y, z);
	}

	std::array< int, 3 > toIndex(const Vector3d<T>& p) const {
		const auto unitLength = getUnitLength();
		const auto ix = static_cast<int>( ( p.getX() - space.getStart().getX() ) / unitLength.getX() );
		const auto iy = static_cast<int>( ( p.getY() - space.getStart().getY() ) / unitLength.getY() );
		const auto iz = static_cast<int>( ( p.getZ() - space.getStart().getZ() ) / unitLength.getZ() );
		return{ ix, iy, iz };
	}

private:
	Space3d<T> space;
	Bitmap3d bmp;

};

	}
}

#endif