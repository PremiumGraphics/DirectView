#ifndef __CRYSTAL_MATH_BITMAP_2D_H__
#define __CRYSTAL_MATH_BITMAP_2D_H__

#include "Bitmap1d.h"

#include <algorithm>

#include <array>

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2>
class Bitmap2d
{
public:
	Bitmap2d()
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

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	size_t size() const { return N1 * N2; }
	
	size_t count() const {
		auto howMany = 0;
		for (const auto& b : bmp1ds) {
			howMany += b.count();
		}
		return howMany;
	}

	bool all() const {
		return count() == size();
		/*
		return std::all_of
		(
			bmp1ds.begin(), bmp1ds.end(),
			[](const Bitmap1d<N>& b) { return b.all(); }
		);
		*/
	}

	bool none() const {
		/*
		return std::none_of(
			bmp1ds.begin(), bmp1ds.end(),
			[](const Bitmap1d<N>& b) {  return b.none(); }
		);
		*/
		for (const auto& b : bmp1ds) {
			if (!b.none() ) {
				return false;
			}
		}
		return true;
	}

	//bool all() const { return count() == size(); }

	//Bitmap1d<N> get1ds() const { return bmp1ds; }

	Bitmap1d<N1> operator[](const std::size_t pos) const { return bmp1ds[pos]; }

	//void add1d(const Bitmap1d<N1>& bmp) { bmp1ds.push_back(bmp); }

private:
	std::array< Bitmap1d<N1>, N2 > bmp1ds;
};

	}
}

#endif