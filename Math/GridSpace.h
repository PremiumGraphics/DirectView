#ifndef __CRYSTAL_MATH_GRID_SPACE_H__
#define __CRYSTAL_MATH_GRID_SPACE_H__

#include "Grid.h"
#include "Space.h"
#include "Discretized.h"

namespace Crystal {
	namespace Math {

template< typename T, typename ValueType >
class GridCell3d
{
public:
	GridCell3d(const Space3d<T>& space, const std::array< ValueType, 8>& values) :
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
class GridSpace3d final {
public:
	GridSpace3d() = default;

	GridSpace3d(const Discretized3d<T>& space, const Grid3d<T>& grid) :
		space(space),
		grid(grid)
	{}

	Vector3d<T> getStart() const { return space.getStart(); }

	//Vector3d<T> getEnd() const { return space.getEnd(); }

	Discretized3d<T> getSpace() const { return space; }

	Grid3d<T> getGrid() const { return grid; }


	std::vector< GridCell3d<T, T> > toCells() const {
		std::vector< GridCell3d<T, T> > cells;

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
			GridCell3d<T, T> c(spaces[i], bs[i]);
			cells.push_back(c);
		}
		return cells;
	}


	/*
	void setBox() {
		for (size_t x = 1; x < grid.getSizeX()-1; ++x) {
			for (size_t y = 1; y < grid.getSizeY()-1; ++y) {
				for (size_t z = 1; z < grid.getSizeZ()-1; ++z) {
					grid[x][y].set(z);
				}
			}
		}
	}

	void setSphere() {
		const Vector3d<T> center(0.5, 0.5, 0.5);
		//const auto lengths = getUnitLengths();
		const T radius = 0.5;//std::min<T>({ lengths.getX(), lengths.getY(), lengths.getZ() } );
		for (size_t x = 0; x < grid.getSizeX(); ++x) {
			for (size_t y = 0; y < grid.getSizeY(); ++y) {
				for (size_t z = 0; z < grid.getSizeZ(); ++z) {
					const auto& norm = getNormalized(x, y, z);
					if (norm.getDistance(center) < radius) {
						grid.set(x,y,z);
					}
				}
			}
		}
	}
	*/


private:
	Discretized3d<T> space;
	Grid3d<T> grid;
};

	}
}

#endif