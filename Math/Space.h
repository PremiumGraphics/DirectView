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

	Vector3d<T> getLengths() const { return vector; }

	T getVolume() const { return vector.getX() * vector.getY() * vector.getZ(); }

	Vector3d<T> getEnd() const { return origin + vector; }

	Vector3d<T> getCenter() const { return origin + vector * 0.5; }

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

	Vector3d<T> getStart() const { return space.getStart(); }

	Vector3d<T> getEnd() const { return space.getEnd(); }

	Space3d<T> getSpace() const { return space; }
	
	Bitmap3d getBitmap() const { return bmp; }

	Vector3d<T> getUnitLengths() const {
		const auto x = space.getLengths().getX() / bmp.getSizeX();
		const auto y = space.getLengths().getY() / bmp.getSizeY();
		const auto z = space.getLengths().getZ() / bmp.getSizeZ();
		return Vector3d<T>(x, y, z);
	}

	T getUnitVolume() const {
		const auto unitLength = getUnitLengths();
		return unitLength.getX() * unitLength.getY() * unitLength.getZ();
	}

	T getVolume() const {
		return bmp.getCount() * getUnitVolume();
	}

	std::array< int, 3 > toIndex(const Vector3d<T>& p) const {
		const auto unitLength = getUnitLengths();
		const auto ix = static_cast<int>( ( p.getX() - space.getStart().getX() ) / unitLength.getX() );
		const auto iy = static_cast<int>( ( p.getY() - space.getStart().getY() ) / unitLength.getY() );
		const auto iz = static_cast<int>( ( p.getZ() - space.getStart().getZ() ) / unitLength.getZ() );
		return{ ix, iy, iz };
	}

	void setBox() const {
		bmp.setAll();
	}

	void setSphere() {
		const Vector3d<T> center(0.5, 0.5, 0.5);
		//const auto lengths = getUnitLengths();
		const T radius = 0.5;//std::min<T>({ lengths.getX(), lengths.getY(), lengths.getZ() } );
		for (size_t x = 0; x < bmp.getSizeX(); ++x) {
			for (size_t y = 0; y < bmp.getSizeY(); ++y) {
				for (size_t z = 0; z < bmp.getSizeZ(); ++z) {
					const auto& norm = getNormalized(x, y, z);
					if (norm.getDistance(center) < radius) {
						bmp[x][y].set(z);
					}
				}
			}
		}
	}

	Vector3d<T> getNormalized(const size_t ix, const size_t iy, const size_t iz) {
		const auto x = ix / static_cast<T>(bmp.getSizeX()) * space.getLengths().getX();
		const auto y = iy / static_cast<T>(bmp.getSizeY()) * space.getLengths().getY();
		const auto z = iz / static_cast<T>(bmp.getSizeZ()) * space.getLengths().getZ();
		return Vector3d<T>(x, y, z) + getUnitLengths() * T(0.5);
	}

private:
	Space3d<T> space;
	Bitmap3d bmp;

};

	}
}

#endif