#ifndef __CRYSTAL_MATH_SCALAR_SPACE_H__
#define __CRYSTAL_MATH_SCALAR_SPACE_H__

#include "Grid.h"
#include "Space.h"
#include "GridSpaceBase.h"

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
class ScalarSpace3d final {
public:
	ScalarSpace3d() = default;

	ScalarSpace3d(const Space3d<T>& space_, const Grid3d<T>& grid) :
		grid( grid ),
		space( space_, grid.getSizes() )
	{
	//	this->space = Discretized3d(space, grid.getSizes());
	}

	Vector3d<T> getStart() const { return space.getStart(); }

	//Vector3d<T> getEnd() const { return space.getEnd(); }

	GridSpaceBase<T> getSpace() const { return space; }

	Grid3d<T> getGrid() const { return grid; }


	std::vector< ScalarCell3d<T, T> > toCells() const {
		std::vector< ScalarCell3d<T, T> > cells;

		const auto lengths = getUnitLengths();
		const Space3d<T>& innerSpace = space.offset(lengths);
		const std::vector< Space3d<T> >& spaces = innerSpace.getDivided(grid.getSizeX() - 1, grid.getSizeY() - 1, grid.getSizeZ() - 1);

		std::vector<std::array<8>> bs;
		for (size_t x = 0; x < grid.getSizeX() - 1; ++x) {
			for (size_t y = 0; y < grid.getSizeY() - 1; ++y) {
				for (size_t z = 0; z < grid.getSizeZ() - 1; ++z) {
					bs.push_back(grid.to8Array(x, y, z));
				}
			}
		}

		assert(spaces.size() == bs.size());

		for (size_t i = 0; i < spaces.size(); ++i) {
			ScalarCell3d<T, T> c(spaces[i], bs[i]);
			cells.push_back(c);
		}
		return cells;
	}


	void setSmooth() {
		const auto& center = space.getCenter();
		const float radius = space.getMinLength() * T(0.5);
		for (size_t x = 0; x < grid.getSizeX(); ++x) {
			for (size_t y = 0; y < grid.getSizeY(); ++y) {
				for (size_t z = 0; z < grid.getSizeZ(); ++z) {
					const auto& pos = space.toCenterPosition( x, y, z);
					if (center.getDistanceSquared(pos) < radius * radius) {
						const auto dist = pos.getDistance(center);
						const auto v = 1.0f - dist / radius;
						grid.set(x, y, z, v);
					}
					else {
						grid.set(x, y, z, 0);
					}
				}
			}
		}
	}

private:
	GridSpaceBase<T> space;
	Grid3d<T> grid;
};

	}
}

#endif