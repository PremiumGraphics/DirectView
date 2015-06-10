#ifndef __CRYSTAL_MATH_SCALAR_SPACE_H__
#define __CRYSTAL_MATH_SCALAR_SPACE_H__

#include "Grid.h"
#include "Space.h"
#include "GridSpaceBase.h"
#include "Kernel.h"

#include <memory>
#include <list>

namespace Crystal {
	namespace Math {

template< typename T, typename ValueType >
class ScalarCell3d
{
public:
	ScalarCell3d(const Space3d<T>& space, const std::array< ValueType, 8>& values) :
		space(space),
		values(values)
	{}

	//getStart() const 

	//std::array<Vector3d<T>, 8> getPositions() const { return }

	Space3d<T> getSpace() const { return space; }

	std::array< ValueType, 8 > getValues() const { return values; }

private:
	Space3d<T> space;
	std::array< ValueType, 8> values;
};


template< typename T >
class ScalarSpace3d : public GridSpaceBase<T> {
public:
	ScalarSpace3d() :
		ScalarSpace3d(Space3d<T>::Unit(), Grid3d<T>(2, 2, 2) )
	{}

	ScalarSpace3d(const Space3d<T>& space_, const Grid3d<T>& grid) :
		GridSpaceBase( space_, grid.getSizes() ),
		grid( grid )
	{
	}

	Grid3d<T> getGrid() const { return grid; }


	std::vector< ScalarCell3d<T, T> > toCells() const {
		std::vector< ScalarCell3d<T, T> > cells;

		const auto lengths = getUnitLengths();
		const Space3d<T>& innerSpace = getSpace().offset(lengths);
		const std::vector< Space3d<T> >& spaces = innerSpace.getDivided(grid.getSizeX() - 1, grid.getSizeY() - 1, grid.getSizeZ() - 1);

		//std::vector<std::array<8>> bs;
		std::vector< std::array<T, 8 > > values;
		for (size_t x = 0; x < grid.getSizeX() - 1; ++x) {
			for (size_t y = 0; y < grid.getSizeY() - 1; ++y) {
				for (size_t z = 0; z < grid.getSizeZ() - 1; ++z) {
					values.push_back(grid.toArray8(x, y, z));
				}
			}
		}

		assert(spaces.size() == values.size());

		for (size_t i = 0; i < spaces.size(); ++i) {
			ScalarCell3d<T, T> c( spaces[i], values[i]);
			cells.push_back(c);
		}
		return cells;
	}


	void add(const Metaball<T>& metaball) {
		const auto center = metaball.getCenter();
		const auto radius = metaball.getRadius();
		for (size_t x = 0; x < grid.getSizeX(); ++x) {
			for (size_t y = 0; y < grid.getSizeY(); ++y) {
				for (size_t z = 0; z < grid.getSizeZ(); ++z) {
					const auto& pos = toCenterPosition( x, y, z);
					if (center.getDistanceSquared(pos) < radius * radius) {
						const auto v = metaball.getValue(pos);
						grid.add(x, y,z, v);
					}
				}
			}
		}
	}

	ScalarSpace3d getOverlapped(const Space3d<T>& rhs) const {
		return ScalarSpace3d(getOverlappedSpace(rhs), getOverlappedGrid(rhs));
	}

	ScalarSpace3d add(const ScalarSpace3d<T>& rhs) const {
		const ScalarSpace3d& ss = getOverlapped(rhs.getSpace());
		ss.getGrid().add(rhs.getGrid());
		return ss;
	}

	ScalarSpace3d sub(const ScalarSpace3d<T>& rhs) const {
		const ScalarSpace3d& ss = getOverlapped(rhs.getSpace());
		ss.getGrid().sub(rhs.getGrid());
		return ss;
	}


private:
	Grid3d<T> grid;

	Grid3d<T> getOverlappedGrid(const Space3d<T>& rhs) const {
		const auto s = getSpace().getOverlapped(rhs);
		const std::array<unsigned int, 3>& startIndex = toIndex(s.getStart());
		const std::array<unsigned int, 3>& endIndex = toIndex(s.getEnd());
		return grid.getSub(startIndex, endIndex);
	}

};

template<typename T>
using ScalarSpace3dSPtr = std::shared_ptr < ScalarSpace3d<T> > ;

template<typename T>
using ScalarSpace3dSPtrList = std::list < ScalarSpace3dSPtr<T> > ;
	}
}

#endif