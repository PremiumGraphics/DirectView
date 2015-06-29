#ifndef __CRYSTAL_MATH_GRID_H__
#define __CRYSTAL_MATH_GRID_H__

#include <vector>
#include <array>
#include <bitset>

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

	Grid1d& set(const unsigned int start, const Grid1d& rhs) {
		for (size_t x = 0; x < rhs.getSize(); ++x) {
			const T v = rhs.get(x);
			set(x + start, v);
		}
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

	/*
	static T getMax() { return 1; }

	static T getMin() { return -1; }
	*/
private:
	std::vector< T > values;

	/*
	T clamp(const T v) {
		return std::min<T>(getMax(), std::max<T>(getMin(), v));
	}
	*/
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

	Grid2d& set(const std::array<unsigned int, 2>& start, const Grid2d& rhs) {
		for (size_t x = 0; x < rhs.getSizeX(); ++x) {
			for (size_t y = 0; y < rhs.getSizeY(); ++y) {
				const T v = rhs.get(x, y);
				set(x + start[0], y + start[1], v);
			}
		}
		return (*this);
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

	~Grid3d() = default;

	Grid3d(const size_t sizex, const size_t sizey, const size_t sizez) :
		grids( sizez, Grid2d<T>(sizex, sizey) )
	{}

	explicit Grid3d(const Grid2dVector<T>& grids) :
		grids(grids)
	{}

	T get(const size_t x, const size_t y, const size_t z) const { return grids[z].get(x,y); }

	void set(const size_t x, const size_t y, const size_t z, const T v) {
		grids[z].set(x, y, v);
	}

	size_t getSizeX() const { return grids.front().getSizeX(); }

	size_t getSizeY() const { return grids.front().getSizeY(); }

	size_t getSizeZ() const { return grids.size(); }

	std::array<unsigned int,3> getSizes() const {
		return { getSizeX(), getSizeY(), getSizeZ() };
	}

	Grid3d getSub(const std::array<unsigned int, 3>& start, const std::array<unsigned int, 3>& end) const {
		Grid2dVector<T> gs(grids.begin() + start[2], grids.begin() + end[2]);
		for (auto& g : gs) {
			g = g.getSub(start[0], end[0], start[1], end[1]);
		}
		return Grid3d(gs);
	}

	Grid3d& add(const size_t x, const size_t y, const size_t z, const T v) {
		const auto vv = this->get(x, y, z) + v;
		this->set(x, y, z, vv);
		return (*this);
	}

	Grid3d& sub(const size_t x, const size_t y, const size_t z, const T v) {
		return add( x, y, z, -v );
	}

	Grid3d& add(const Grid3d& rhs) {
		for (size_t x = 0; x < getSizeX(); ++x) {
			for (size_t y = 0; y < getSizeY(); ++y) {
				for (size_t z = 0; z < getSizeZ(); ++z) {
					const auto v = rhs.get(x, y, z);
					add(x, y, z, v);
				}
			}
		}
		return (*this);
	}

	Grid3d& sub(const Grid3d& rhs) {
		for (size_t x = 0; x < getSizeX(); ++x) {
			for (size_t y = 0; y < getSizeY(); ++y) {
				for (size_t z = 0; z < getSizeZ(); ++z) {
					const auto v = rhs.get(x, y, z);
					sub(x, y, z, v);
				}
			}
		}
		return (*this);
	}

	Grid3d& set(const std::array<unsigned int, 3>& start, const Grid3d& rhs) {
		for (size_t x = 0; x < rhs.getSizeX(); ++x) {
			for (size_t y = 0; y < rhs.getSizeY(); ++y) {
				for (size_t z = 0; z < rhs.getSizeZ(); ++z) {
					const T v = rhs.get(x, y, z);
					set(x + start[0], y + start[1], z + start[2], v);
				}
			}
		}
		return (*this);
	}


	std::array< T, 8 > toArray8(const size_t i, const size_t j, const size_t k) const {
		return std::array < T, 8 > {
				get(i, j, k),
				get(i+1, j, k),
				get(i+1, j+1, k),
				get(i, j+1, k),
				get(i, j, k+1),
				get(i+ 1, j, k+1),
				get(i+ 1, j+1, k+1),
				get(i, j+1, k+1)
		};
	}

	bool isAllLower(const size_t i, const size_t j, const size_t k, const T t) const {
		assert(i < getSizeX() && j < getSizeY() && k < getSizeZ());
		std::bitset<8> bs;
		bs.set(0, isLower(i, j, k, t));
		bs.set(1, isLower(i + 1, j, k, t));
		bs.set(2, isLower(i + 1, j + 1, k, t));
		bs.set(3, isLower(i, j + 1, k, t));
		bs.set(4, isLower(i, j, k + 1, t));
		bs.set(5, isLower(i + 1, j, k + 1, t));
		bs.set(6, isLower(i + 1, j + 1, k + 1, t));
		bs.set(7, isLower(i, j + 1, k + 1, t));
		return (bs.all());
	}

	bool isAllHigher(const size_t i, const size_t j, const size_t k, const T t) const {
		assert(i < getSizeX() && j < getSizeY() && k < getSizeZ());
		std::bitset<8> bs;
		bs.set(0, isHigher(i, j, k, t));
		bs.set(1, isHigher(i + 1, j, k, t));
		bs.set(2, isHigher(i + 1, j + 1, k, t));
		bs.set(3, isHigher(i, j + 1, k, t));
		bs.set(4, isHigher(i, j, k + 1, t));
		bs.set(5, isHigher(i + 1, j, k + 1, t));
		bs.set(6, isHigher(i + 1, j + 1, k + 1, t));
		bs.set(7, isHigher(i, j + 1, k + 1, t));
		return (bs.all());
	}

	bool isNotBoundary(const size_t i, const size_t j, const size_t k, const T threshold) const {
		return isAllLower(i, j, k, threshold) || isAllHigher(i, j, k, threshold);
	}

	bool isBoundary(const size_t i, const size_t j, const size_t k, const T threshold) const {
		return !isNotBoundary(i, j, k, threshold);
	}

	bool isLower(const size_t i , const size_t j, const size_t k ,const T threshold) const {
		return (get(i, j, k) < threshold);
	}

	bool isHigher(const size_t i, const size_t j, const size_t k, const T threshold) const {
		return !isLower(i, j, k, threshold);
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