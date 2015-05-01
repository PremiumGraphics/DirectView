#ifndef __CRYSTAL_MATH_BITMAP_2D_H__
#define __CRYSTAL_MATH_BITMAP_2D_H__

#include "Bitmap1d.h"

namespace Crystal {
	namespace Math {

template<size_t N>
class Bitmap2d
{
public:
	Bitmap2d()
	{}

	Bitmap2d(const size_t dim) :
		bmp1ds(dim)
	{}

	void set(const unsigned int x, const unsigned int y) { bmp1ds[x][y] = true; }

	void reset(const unsigned int x, const unsigned int y) { bmp1ds[x][y] = false; }

	size_t size() const { return bmp1ds.size(); }

	size_t count() const {
		auto howMany = 0;
		for (const auto& b : bmp1ds) {
			howMany += b.count();
		}
		return howMany;
	}

	bool none() const {
		for (const auto& b : bmp1ds) {
			if (!b.none() ) {
				return false;
			}
		}
		return true;
	}

	//bool all() const { return count() == size(); }

	std::vector< Bitmap1d<N> > get1ds() const { return bmp1ds; }

	Bitmap1d<N> operator[](const std::size_t pos) const { return bmp1ds[pos]; }

	void add1d(const Bitmap1d<N>& bmp) { bmp1ds.push_back(bmp); }

private:
	std::vector< Bitmap1d<N> > bmp1ds;
};

template<size_t N>
class Bitmap3d
{
public:
	Bitmap3d()
	{}

	Bitmap3d(const size_t dim, const size_t size2d) :
		bmp2ds(dim, size2d)
	{}

	void set(const size_t x, const size_t y, const size_t z) { bmp2ds[z].set(x,y); }

	void reset(const size_t x, const size_t y, const size_t z) { bmp2ds[z].reset(x,y); }

	//std::vector< Bitmap2d<N> > get2ds() const { return bmp2ds; }

	Bitmap2d<N> operator[](const std::size_t pos) const { return bmp2ds[pos]; }

	size_t size() const { return bmp2ds.size(); }

	/*
	void set(const unsigned int x, const unsigned int y) { bmp1ds[x][y] = true; }

	void reest(const unsigned int x, const unsigned int y) { bmp1ds[x][y] = false; }

	std::vector< Bitmap1d<N> > get1ds() const { return bmp1ds; }

	Bitmap1d<N> operator[](const std::size_t pos) const { return bmp1ds[pos]; }

	void add1d(const Bitmap1d& bmp) { bmp1ds.push_back(bmp); }
	*/

private:
	std::vector< Bitmap2d<N> > bmp2ds;
};

	}
}

#endif