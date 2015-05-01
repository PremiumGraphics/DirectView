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

	void set() {
		for (auto& b : bmp1ds) {
			b.set();
		}
	}

	void reset() {
		for (auto& b : bmp1ds) {
			b.reset();
		}
	}

	void set(const unsigned int x, const unsigned int y) { bmp1ds[x][y] = true; }

	void reset(const unsigned int x, const unsigned int y) { bmp1ds[x][y] = false; }

	size_t size1d() const {
		return bmp1ds.front().size();
	}

	size_t size2d() const {
		return bmp1ds.size();
	}

	size_t size() const {
		auto s = 0;
		for (const auto& b : bmp1ds) {
			s += b.size();
		}
		return s;
	}

	size_t count() const {
		auto howMany = 0;
		for (const auto& b : bmp1ds) {
			howMany += b.count();
		}
		return howMany;
	}

	bool all() const {
		return count() == size();
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

	}
}

#endif