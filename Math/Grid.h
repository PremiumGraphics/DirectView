#ifndef __CRYSTAL_MATH_GRID_H__
#define __CRYSTAL_MATH_GRID_H__

#include <vector>

namespace Crystal {
	namespace Math{

template<typename T>
class Grid1d final
{
public:
	Grid1d() = default;

	explicit Grid1d(const size_t size) :values(size)
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
	//T& operator[](const size_t i) { return &(values[i]); }

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

	T get(const size_t x, const size_t y) const { return grids[y].get(x); }

	Grid2d& set(const size_t x, const size_t y, const T v) {
		grids[y].set(x, v);
		return (*this);
	}

	size_t getSizeX() const { return grids.front().getSize(); }

	size_t getSizeY() const { return grids.size(); }

private:
	Grid1dVector<T> grids;
};

template<typename T>
using Grid2dVector = std::vector < Grid2d<T> > ;

/*
template<typename T>
class Grid3d final
{
public:
	Grid3d() = default;

	Grid3d(const size_t sizex, const size_t sizey, const size_t z) :
		grids( Grid2d( )
	{}

	T get(const size_t x, const size_t y) const { return grids[x].get(y); }

	Grid2d& set(const size_t x, const size_t y, const T v) {
		grids[x].set(y, v);
		return (*this);
	}

	size_t getSizeX() const { return grids.size(); }

	size_t getSizeY() const { return grids.front().getSize(); }

private:
	std::vector< Grid2d<T> > grids;
};
*/

	}
}

#endif