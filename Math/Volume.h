#ifndef __CRYSTAL_MATH_VOLUME_H__
#define __CRYSTAL_MATH_VOLUME_H__

#include "Grid.h"
#include "Space.h"
#include "GridSpaceBase.h"
#include "Particle.h"

#include <memory>
#include <list>

namespace Crystal {
	namespace Math {

template< typename T, typename ValueType >
class VolumeCell3d
{
public:
	VolumeCell3d(const Space3d<T>& space, const std::array< ValueType, 8>& values) :
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
class Volume3d : public GridSpaceBase<T> {
public:
	Volume3d() :
		Volume3d(Space3d<T>::Unit(), Grid3d<T>(2, 2, 2) )
	{}

	Volume3d(const Space3d<T>& space_, const Grid3d<T>& grid) :
		GridSpaceBase( space_, grid.getSizes() ),
		grid( grid )
	{
	}

	Volume3d(const Particle3d<T>& particle, const Grid3d<T>& grid) :
		GridSpaceBase(particle.getBoundingSpace(), grid.getSizes()),
		grid( grid )
	{
		add(particle);
	}

	void setValue(const T v) {
		for (size_t x = 0; x < grid.getSizeX(); ++x) {
			for (size_t y = 0; y < grid.getSizeY(); ++y) {
				for (size_t z = 0; z < grid.getSizeZ(); ++z) {
					grid.set(x, y, z, v);
				}
			}
		}
	}

	std::vector<T> getValues() const {
		std::vector<T> values;
		for (size_t x = 0; x < grid.getSizeX(); ++x) {
			for (size_t y = 0; y < grid.getSizeY(); ++y) {
				for (size_t z = 0; z < grid.getSizeZ(); ++z) {
					values.push_back( grid.get(x, y, z) );
				}
			}
		}
		return values;
	}

	Grid3d<T> getGrid() const { return grid; }


	std::vector< VolumeCell3d<T, T> > toCells() const {
		std::vector< VolumeCell3d<T, T> > cells;

		const auto& lengths = getUnitLengths();
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
			VolumeCell3d<T, T> c( spaces[i], values[i]);
			cells.push_back(c);
		}
		return cells;
	}


	void add(const Particle3d<T>& metaball, const T factor) {
		const auto center = metaball.getCenter();
		const auto radius = metaball.getRadius();
		//const Math::Vector3d<T> startPosition( center.getX()
		//const Index3d startIndex = toIndex(metaball.getMinPosition());
		//const Index3d endIndex = toIndex(metaball.getMaxPosition());
		//for (size_t x = startIndex[0]; x < endIndex[0]; ++x) {
		//	for (size_t y = startIndex[1]; y < endIndex[1]; ++y) {
		//		for (size_t z = startIndex[2]; z < endIndex[2]; ++z) {
		for (size_t x = 0; x < getSizeX(); ++x ) {
			for (size_t y = 0; y < getSizeY(); ++y) {
				for (size_t z = 0; z < getSizeZ(); ++z) {
					const auto& pos = toCenterPosition( x, y, z);
					if (center.getDistanceSquared(pos) < radius * radius) {
						const auto v = metaball.getValue(pos) * factor;
						grid.add(x, y,z, v);
					}
				}
			}
		}
	}

	Volume3d getOverlapped(const Space3d<T>& rhs) const {
		return Volume3d(getOverlappedSpace(rhs), getOverlappedGrid(rhs));
	}

	Volume3d add(const Volume3d<T>& rhs) const {
		const Volume3d& ss = getOverlapped(rhs.getSpace());
		ss.getGrid().add(rhs.getGrid());
		return ss;
	}

	Volume3d sub(const Volume3d<T>& rhs) const {
		const Volume3d& ss = getOverlapped(rhs.getSpace());
		ss.getGrid().sub(rhs.getGrid());
		return ss;
	}

	Volume3d& operator+=(const Volume3d<T>& rhs) {
		for (size_t x = 0; x < getSizeX(); ++x) {
			for (size_t y = 0; y < getSizeY(); ++y) {
				for (size_t z = 0; z < getSizeZ(); ++z) {
					const auto v = rhs.grid.get(x, y, z);
					grid.add( x,y,z,v);
				}
			}
		}
		return (*this);
	}

	/*
	Volume3d createAdd(const Volume3d<T>& rhs) const {
		const auto space = getSpace().createBoundingSpace(rhs.getSpace());
		const auto grid1 = grid;
		grid1.add(rhs.getGrid());
		return Volume3d(space, grid1);
	}
	*/

	/*
	static T getMax() { return Grid3; }

	static T getMin() { return -1; }
	*/

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
using Volume3dSPtr = std::shared_ptr < Volume3d<T> > ;

template<typename T>
using Volume3dSPtrList = std::list < Volume3dSPtr<T> > ;
	}
}

#endif