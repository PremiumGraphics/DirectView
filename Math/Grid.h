#ifndef __CRYSTAL_MATH_GRID_H__
#define __CRYSTAL_MATH_GRID_H__

#include <vector>
#include <array>

namespace Crystal {
	namespace Math{

template<typename T>
class Grid1d final
{
public:
	Grid1d() = default;

	explicit Grid1d(const size_t size) :values(size)
	{}

	explicit Grid1d(const std::vector<T>& values) :
		values(values)
	{}

	Grid1d(const size_t size, const T v) : values(size, v)
	{}

	~Grid1d() = default;

	size_t getSize() const { return values.size(); }

	T get(const size_t i) const { return values[i]; }

	Grid1d& set(const size_t i, const T v) {
		this->values[i] = v;
		return (*this);
	}

	Grid1d getSub(const size_t startIndex, const size_t endIndex) const {
		std::vector<T> bs(values.begin() + startIndex, values.begin() + endIndex);
		return Grid1d(bs);
	}

	bool equals(const Grid1d& rhs) const {
		return values == rhs.values;
	}

	bool operator==(const Grid1d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Grid1d& rhs) const {
		return !equals(rhs);
	}


private:
	std::vector< T > values;
};

template<typename T>
using Grid1dVector = std::vector < Grid1d<T> > ;

template<typename T>
class Grid2d final
{
public:
	Grid2d() = default;

	Grid2d(const size_t sizex, const size_t sizey) :
		grids(sizey, Grid1d<T>(sizex))
	{}

	explicit Grid2d(const Grid1dVector<T>& grids) :
		grids( grids )
	{}

	T get(const size_t x, const size_t y) const { return grids[y].get(x); }

	Grid2d& set(const size_t x, const size_t y, const T v) {
		grids[y].set(x, v);
		return (*this);
	}

	size_t getSizeX() const { return grids.front().getSize(); }

	size_t getSizeY() const { return grids.size(); }

	Grid2d getSub(const size_t startx, const size_t endx, const size_t starty, const size_t endy) const {
		Grid1dVector<T> gs(grids.begin() + starty, grids.begin() + endy);
		for (auto& g : gs) {
			g = g.getSub(startx, endx);
		}
		return Grid2d(gs);
	}

	bool equals(const Grid2d& rhs) const {
		return grids == rhs.grids;
	}

	bool operator==(const Grid2d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Grid2d& rhs) const {
		return !equals(rhs);
	}

private:
	Grid1dVector<T> grids;
};

template<typename T>
using Grid2dVector = std::vector < Grid2d<T> > ;

template<typename T>
class Grid3d final
{
public:
	Grid3d() = default;

	Grid3d(const size_t sizex, const size_t sizey, const size_t sizez) :
		grids( sizez, Grid2d<T>(sizex, sizey) )
	{}

	explicit Grid3d(const Grid2dVector<T>& grids) :
		grids(grids)
	{}

	T get(const size_t x, const size_t y, const size_t z) const { return grids[z].get(x,y); }

	Grid3d& set(const size_t x, const size_t y, const size_t z, const T v) {
		grids[z].set(x, y, v);
		return (*this);
	}

	size_t getSizeX() const { return grids.front().getSizeX(); }

	size_t getSizeY() const { return grids.front().getSizeY(); }

	size_t getSizeZ() const { return grids.size(); }

	std::array<unsigned int,3> getSizes() const {
		return { getSizeX(), getSizeY(), getSizeZ() };
	}

	Grid3d getSub(const std::array<unsigned int, 3>& start, const std::array<unsigned int, 3>& end) {
		Grid2dVector<T> gs(grids.begin() + start[2], grids.begin() + end[2]);
		for (auto& g : gs) {
			g = g.getSub(start[0], end[0], start[1], end[1]);
		}
		return Grid3d(gs);
	}


	std::array< T, 8 > toArray8(const size_t i, const size_t j, const size_t k) const {
		return std::array < T, 8 > {
				get(i, j, k),
				get(i + 1, j, k),
				get(i + 1, j + 1, k),
				get(i, j + 1, k),
				get(i, j, k + 1),
				get(i + 1, j, k + 1),
				get(i + 1, j + 1, k + 1),
				get(i, j + 1, k + 1)
		};

		/*
		std::bitset<8> to8Bit(const size_t i, const size_t j, const size_t k) const {
			std::bitset<8> b;
			if (get(i, j, k))		{ b.set(0); }
			if (get(i + 1, j, k))	{ b.set(1); }
			if (get(i + 1, j + 1, k))	{ b.set(2); }
			if (get(i, j + 1, k))	{ b.set(3); }
			if (get(i, j, k + 1))	{ b.set(4); }
			if (get(i + 1, j, k + 1))	{ b.set(5); }
			if (get(i + 1, j + 1, k + 1)){ b.set(6); }
			if (get(i, j + 1, k + 1))	{ b.set(7); }

			return b;
			*/
	}

	bool equals(const Grid3d& rhs) const {
		return grids == rhs.grids;
	}

	bool operator==(const Grid3d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Grid3d& rhs) const {
		return !equals(rhs);
	}


private:
	Grid2dVector<T> grids;
};

	}
}

#endif