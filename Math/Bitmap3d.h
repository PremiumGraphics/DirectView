#ifndef __CRYSTAL_MATH_BITMAP_3D_H__
#define __CRYSTAL_MATH_BITMAP_3D_H__

#include "Bitmap2d.h"

namespace Crystal {
	namespace Math {

template<size_t N>
class Bitmap3d
{
public:
	Bitmap3d()
	{}

	Bitmap3d(const size_t dim, const size_t size2d) :
		bmp2ds(dim, size2d)
	{}

	size_t size() const {
		auto s = 0;
		for (const auto& b : bmp2ds) {
			s += b.size();
		}
		return s;
	}


	size_t count() const {
		auto howMany = 0;
		for (const auto& b : bmp2ds) {
			howMany += b.count();
		}
		return howMany;
	}


	void set(const size_t x, const size_t y, const size_t z) { bmp2ds[z].set(x, y); }

	void reset(const size_t x, const size_t y, const size_t z) { bmp2ds[z].reset(x, y); }

	//std::vector< Bitmap2d<N> > get2ds() const { return bmp2ds; }

	Bitmap2d<N> operator[](const std::size_t pos) const { return bmp2ds[pos]; }


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