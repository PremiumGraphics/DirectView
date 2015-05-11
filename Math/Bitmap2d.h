#ifndef __CRYSTAL_MATH_BITMAP_2D_H__
#define __CRYSTAL_MATH_BITMAP_2D_H__

#include "Bitmap1d.h"

#include <algorithm>

#include <array>

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2>
class Bitmap2d final
{
public:
	Bitmap2d() = default;

	~Bitmap2d() = default;

	explicit Bitmap2d(const Bitmap1dArray<N1,N2>& b) :
		bmp1ds(b)
	{}

	explicit Bitmap2d(const std::string& str) {
		byString(str);
	}

	explicit Bitmap2d(const std::array<std::string, N2>& strs) {
		byStrings(strs);
	}

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

	void set(const unsigned int x, const unsigned int y) { bmp1ds[x].set(y); }

	void set(const unsigned int x, const Bitmap1d<N1>& b) { bmp1ds[x] = b; }

	void reset(const unsigned int x, const unsigned int y) { bmp1ds[x].reset(y); }

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


	Bitmap1d<N1>& operator[](const std::size_t pos) { return bmp1ds[pos]; }

	Bitmap1d<N1> operator[](const std::size_t pos) const { return bmp1ds[pos]; }


	//void add1d(const Bitmap1d<N1>& bmp) { bmp1ds.push_back(bmp); }

	bool equals(const Bitmap2d<N1, N2>& rhs) const {
		return bmp1ds == rhs.bmp1ds;
	}

	bool operator==(const Bitmap2d<N1, N2>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Bitmap2d<N1, N2>& rhs) const {
		return !equals(rhs);
	}

	Bitmap2d<N1, N2>& operator^=(const Bitmap2d<N1, N2>& rhs) {
		for (size_t i = 0; i < N1; ++i) {
			bmp1ds[i] ^= rhs[i];
		}
		return (*this);
	}

	Bitmap2d<N1, N2>& operator|=(const Bitmap2d<N1, N2>& rhs) {
		for (size_t i = 0; i < N1; ++i) {
			bmp1ds[i] |= rhs[i];
		}
		return (*this);
	}

	Bitmap2d<N1,N2>& operator&=(const Bitmap2d<N1,N2>& rhs) {
		for (size_t i = 0; i < N1; ++i) {
			bmp1ds[i] &= rhs[i];
		}
		return (*this);
	}

	std::string toString() const {
		std::string str;
		for (const auto& b : bmp1ds) {
			str += b.toString();
		}
		return str;
	}

	void byString(const std::string& str) {
		assert(str.size() == this->size());
		std::array< std::string, N2 > strs;
		for (size_t i = 0; i < N2; ++i) {
			const size_t start = i * N1;
			const size_t end = (i + 1) * N1;
			strs[i] = str.substr( start, end );
		}
		byStrings(strs);
	}

	void byStrings(const std::array<std::string, N2>& strs) {
		for (size_t i = 0; i < N2; ++i) {
			bmp1ds[i] = Bitmap1d<N1>(strs[i]);
		}
	}

private:
	Bitmap1dArray< N1, N2 > bmp1ds;
};

template<size_t N1, size_t N2, size_t N3>
using Bitmap2dArray = std::array < Bitmap2d<N1, N2>, N3 > ;
	}
}

#endif