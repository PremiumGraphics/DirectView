#ifndef __CRYSTAL_MATH_BIT_SPACE_H__
#define __CRYSTAL_MATH_BIT_SPACE_H__

#include "Bitmap.h"
#include "Space.h"

namespace Crystal {
	namespace Math {

template< typename T >
class BitCell3d
{
public:
	BitCell3d(const Space3d<T>& space, const std::bitset<8>& values ) :
		space( space ),
		values( values )
	{}

	//getStart() const 

	//std::array<Vector3d<T>, 8> getPositions() const { return }

	Space3d<T> getSpace() const { return space; }

	std::bitset<8> getValues() const { return values; }

private:
	Space3d<T> space;
	std::bitset<8> values;
};

template< typename T >
class BitSpace3d final {
public:
	BitSpace3d() = default;

	BitSpace3d(const Space3d<T>& space, const Bitmap3d& bmp) :
		space(space),
		bmp(bmp)
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
		const auto ix = static_cast<int>((p.getX() - space.getStart().getX()) / unitLength.getX());
		const auto iy = static_cast<int>((p.getY() - space.getStart().getY()) / unitLength.getY());
		const auto iz = static_cast<int>((p.getZ() - space.getStart().getZ()) / unitLength.getZ());
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

	std::vector< BitCell3d<T> > toCells() const {
		std::vector< BitCell3d<T> > cells;

		const std::vector< Space3d<T> >& spaces = space.getDivided( bmp.getSizeX(), bmp.getSizeY(), bmp.getSizeZ() );

		std::vector<bool> bs;
		for (size_t x = 0; x < bmp.getSizeX(); ++x) {
			for (size_t y = 0; y < bmp.getSizeY(); ++y) {
				for (size_t z = 0; z < bmp.getSizeZ(); ++z) {
					bs.push_back(bmp[x][y][z]);
				}
			}
		}

		for (size_t i = 0; i < cells.size(); ++i) {
			Cell3d<T, bool> c(spaces[i], bs[i]);
			cells.push_back(c);
		}
		return cells;
	}

private:
	Space3d<T> space;
	Bitmap3d bmp;

};

	}
}

#endif