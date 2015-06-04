#ifndef __CRYSTAL_MATH_BIT_SPACE_H__
#define __CRYSTAL_MATH_BIT_SPACE_H__

#include "Bitmap.h"
#include "Space.h"
#include "GridSpaceBase.h"

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

	Space3d<T> getSpace() const { return space; }

	std::bitset<8> getValues() const { return values; }

private:
	Space3d<T> space;
	std::bitset<8> values;
};

template< typename T >
class BitSpace3d : public GridSpaceBase<T> {
public:
	BitSpace3d() = default;

	explicit BitSpace3d(const Bitmap3d& bmp) :
		GridSpaceBase(Space3d<T>::Unit(), bmp.getSizes() ),
		bmp( bmp)
	{}

	BitSpace3d(const Space3d<T>& space, const Bitmap3d& bmp) :
		GridSpaceBase(space, bmp.getSizes() ),
		bmp(bmp)
	{}

	Vector3d<T> getStart() const { return space.getStart(); }

	Vector3d<T> getEnd() const { return space.getEnd(); }

	Bitmap3d getBitmap() const { return bmp; }

	std::array< unsigned int, 3 > getResolution() const { return bmp.getSizes(); }

	/*
	T getVolume() const {
		return bmp.getCount() * getUnitVolume();
	}
	*/


	void setBox() {
		for (size_t x = 1; x < bmp.getSizeX()-1; ++x) {
			for (size_t y = 1; y < bmp.getSizeY()-1; ++y) {
				for (size_t z = 1; z < bmp.getSizeZ()-1; ++z) {
					bmp.set(x,y,z);
				}
			}
		}
	}

	BitSpace3d& setSphere() {
		const Vector3d<T>& center = getCenter();
		const auto unitLength = getUnitLengths();
		const T radius = ( getSpace().getLengths().getX() - unitLength.getX() ) * T(0.5);
		for (size_t x = 0; x < bmp.getSizeX(); ++x) {
			for (size_t y = 0; y < bmp.getSizeY(); ++y) {
				for (size_t z = 0; z < bmp.getSizeZ(); ++z) {
					const auto pos = toCenterPosition(x, y, z);
					const auto distSquared = pos.getDistanceSquared(center);
					if ( distSquared < radius * radius) {
						bmp.set(x,y,z);
					}
				}
			}
		}
		return (*this);
	}


	std::vector< BitCell3d<T> > toCells() const {
		std::vector< BitCell3d<T> > cells;

		const auto lengths = getUnitLengths();
		const Space3d<T>& innerSpace = getSpace().offset( lengths );
		const std::vector< Space3d<T> >& spaces = innerSpace.getDivided( bmp.getSizeX()-1, bmp.getSizeY()-1, bmp.getSizeZ()-1 );

		std::vector<std::bitset<8>> bs;
		for (size_t x = 0; x < bmp.getSizeX()-1; ++x) {
			for (size_t y = 0; y < bmp.getSizeY()-1; ++y) {
				for (size_t z = 0; z < bmp.getSizeZ()-1; ++z) {
					bs.push_back(bmp.to8Bit(x, y, z));
				}
			}
		}

		assert(spaces.size() == bs.size());

		for (size_t i = 0; i < spaces.size(); ++i) {
			BitCell3d<T> c(spaces[i], bs[i]);
			cells.push_back(c);
		}
		return cells;
	}

	std::vector< Space3d<T> > toEnabledSpaces() const {
		std::vector< Space3d<T> > results;

		const std::vector< Space3d<T> >& spaces = getSpace().getDivided(bmp.getSizeX(), bmp.getSizeY(), bmp.getSizeZ() );
		int i = 0;
		for (size_t x = 0; x < bmp.getSizeX(); ++x) {
			for (size_t y = 0; y < bmp.getSizeY(); ++y) {
				for (size_t z = 0; z < bmp.getSizeZ(); ++z) {
					if (bmp.get(x,y,z)) {
						results.push_back(spaces[i]);
					}
					i++;
				}
			}
		}
		return results;
	}

	Vector3dVector<T> toEnabledPositions() const {
		Vector3dVector<T> positions;
		const auto& spaces = toEnabledSpaces();
		for (const auto& s : spaces) {
			positions.push_back( s.getCenter() );
		}
		return positions;
	}

	/*
	Bitmap3d getSubBitmap(const Space3d<T>& rhs) const {
		const auto s = getSpace().getOverlapped(rhs);
		return bmp.getSub(startIndex[0], endIndex[0], startIndex[1], endIndex[1], startIndex[2], endIndex[2]);
	}
	*/


	BitSpace3d getOverlapped(const BitSpace3d<T>& rhs) const {
		return getOverlapped(rhs.getSpace());
	}

	BitSpace3d getOverlapped(const Space3d<T>& rhs) const {
		const auto& s = getOverlappedSpace(rhs);
		const auto& b = getOverlappedBitmap(rhs);
		return BitSpace3d(s, b);
	}

	/*
	BitSpace3d& setOverlapped(const Space3d<T>& rhs) const {

	}
	*/

	BitSpace3d and(const BitSpace3d<T>& rhs) const {
		const BitSpace3d& bs = getOverlapped(rhs);
		bs.getBitmap().and(rhs.getBitmap());
		return bs;
	}

	BitSpace3d or(const BitSpace3d<T>& rhs) const {
		const BitSpace3d& bs = getOverlapped(rhs);
		bs.getBitmap().or(rhs.getBitmap());
		return bs;
	}

	BitSpace3d& not() {
		bmp.not();
		return (*this);
	}

	/*
	BitSpace3d getSubSpace(const Vector3d<T>& v) const {
		const auto toIndex(v);
		Bitmap3d bmp;
		return BitSpace3d(space.moveEnd(v), bmp);
	}
	*/

	bool equals(const BitSpace3d<T>& rhs) const {
		return
			(getSpace() == rhs.getSpace()) &&
			(getBitmap() == rhs.getBitmap());
	}

	bool operator==(const BitSpace3d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const BitSpace3d<T>& rhs) const {
		return !equals(rhs);
	}

private:
	Bitmap3d bmp;

private:
	Bitmap3d getOverlappedBitmap(const Space3d<T>& rhs) const {
		const auto s = getSpace().getOverlapped(rhs);
		const std::array<unsigned int, 3>& startIndex = toIndex(s.getStart());
		const std::array<unsigned int, 3>& endIndex = toIndex(s.getEnd());
		return bmp.getSub(startIndex, endIndex);
	}

	Space3d<T> getOverlappedSpace(const Space3d<T>& rhs) const {
		return getSpace().getOverlapped(rhs);
	}



};

	}
}

#endif