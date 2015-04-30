#ifndef __CRYSTAL_MATH_BITMAP_1D_H__
#define __CRYSTAL_MATH_BITMAP_1D_H__

#include <bitset>

namespace Crystal {
	namespace Math {

template<size_t N>
using Bitmap1d = std::bitset <N> ;

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

	Bitmap3d(const size_t dim) :
		bmp2ds(dim)
	{}

	void set(const size_t x, const size_t y, const size_t z) { bmp2ds[x][y][z] = true; }

	void reset(const size_t x, const size_t y, const size_t z) { bmp2ds[x][y][z] = false; }

	//std::vector< Bitmap2d<N> > get2ds() const { return bmp2ds; }

	//Bitmap2d<N> operator[](const std::size_t pos) const { return bmp2ds[pos]; }

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