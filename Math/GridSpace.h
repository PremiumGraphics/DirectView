#ifndef __CRYSTAL_MATH_GRID_SPACE_H__
#define __CRYSTAL_MATH_GRID_SPACE_H__

#include "Grid.h"
#include "Space.h"

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

	GridSpace3d(const Space3d<T>& space, const Grid3d<T>& grid) :
		space(space),
		grid(grid)
	{}

	Vector3d<T> getStart() const { return space.getStart(); }

	Vector3d<T> getEnd() const { return space.getEnd(); }

	Space3d<T> getSpace() const { return space; }

	Grid3d<T> getGrid() const { return grid; }

	Vector3d<T> getUnitLengths() const {
		const auto x = space.getLengths().getX() / grid.getSizeX();
		const auto y = space.getLengths().getY() / grid.getSizeY();
		const auto z = space.getLengths().getZ() / grid.getSizeZ();
		return Vector3d<T>(x, y, z);
	}

	T getUnitVolume() const {
		const auto unitLength = getUnitLengths();
		return unitLength.getX() * unitLength.getY() * unitLength.getZ();
	}

	std::array< int, 3 > toIndex(const Vector3d<T>& p) const {
		const auto unitLength = getUnitLengths();
		const auto ix = static_cast<int>((p.getX() - space.getStart().getX()) / unitLength.getX());
		const auto iy = static_cast<int>((p.getY() - space.getStart().getY()) / unitLength.getY());
		const auto iz = static_cast<int>((p.getZ() - space.getStart().getZ()) / unitLength.getZ());
		return{ ix, iy, iz };
	}

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

	Vector3d<T> getNormalized(const size_t ix, const size_t iy, const size_t iz) const {
		const auto x = ix / static_cast<T>(grid.getSizeX()) * space.getLengths().getX();
		const auto y = iy / static_cast<T>(grid.getSizeY()) * space.getLengths().getY();
		const auto z = iz / static_cast<T>(grid.getSizeZ()) * space.getLengths().getZ();
		return Vector3d<T>(x, y, z) + getUnitLengths() * T(0.5);
	}

private:
	Space3d<T> space;
	Grid3d<T> grid;
};

	}
}

#endif