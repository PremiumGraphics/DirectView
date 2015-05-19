#ifndef __CRYSTAL_MATH_BITMAP_2D_H__
#define __CRYSTAL_MATH_BITMAP_2D_H__

#include "Bitmap1d.h"

#include <algorithm>

#include <array>
#include <queue>

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2>
class Bitmap2d final
{
public:
	Bitmap2d() = default;

	~Bitmap2d() = default;

	explicit Bitmap2d(const long l)
	{}

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

	void set(const unsigned int x, const unsigned int y) { bmp1ds[y].set(x); }

	void set(const unsigned int x, const Bitmap1d<N1>& b) { bmp1ds[x] = b; }

	bool get(const unsigned int x, const unsigned int y) const { return bmp1ds[y][x]; }

	void reset(const unsigned int x, const unsigned int y) { bmp1ds[y].reset(x); }

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

	bool isAll() const {
		return count() == size();
	}

	bool isNone() const {
		/*
		return std::none_of(
			bmp1ds.begin(), bmp1ds.end(),
			[](const Bitmap1d<N>& b) {  return b.none(); }
		);
		*/
		for (const auto& b : bmp1ds) {
			if (!b.isNone() ) {
				return false;
			}
		}
		return true;
	}

	Bitmap2d<N1, N2>& and( const Bitmap2d<N1,N2>& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].and( rhs.bmp1ds[i] );
		}
		return (*this);
	}

	Bitmap2d<N1, N2>& or(const Bitmap2d<N1, N2>& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].or(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d<N1, N2>& xor(const Bitmap2d<N1, N2>& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].xor(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d<N1, N2> not() const {
		Bitmap1dArray<N1, N2> bs;
		for (size_t i = 0; i < bmp1ds.size(); ++i ) {
			bs[i] = bmp1ds[i].not();
		}
		return Bitmap2d<N1, N2>(bs);
	}

	/*
	Bitmap1d<N1>& operator[](const std::size_t pos) { return bmp1ds[pos]; }

	Bitmap1d<N1> operator[](const std::size_t pos) const { return bmp1ds[pos]; }
	*/

	bool equals(const Bitmap2d<N1, N2>& rhs) const {
		return bmp1ds == rhs.bmp1ds;
	}

	bool operator==(const Bitmap2d<N1, N2>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Bitmap2d<N1, N2>& rhs) const {
		return !equals(rhs);
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
			const size_t len = N1;
			strs[i] = str.substr( start, len );
		}
		byStrings(strs);
	}

	void byStrings(const std::array<std::string, N2>& strs) {
		for (size_t i = 0; i < N2; ++i) {
			bmp1ds[i] = Bitmap1d<N1>(strs[i]);
		}
	}

	Bitmap2d<N1, N2> getEdgesx() const {
		Bitmap2d<N1, N2 > dest;
		for (size_t x = 0; x < sizex(); ++x) {
			for (size_t y = 1; y < sizey(); ++y){
				if ( bmp1ds[x][y - 1] != bmp1ds[x][y]) {
					dest.set(x, y);
				}
			}
		}
		return dest;
	}

	Bitmap2d<N1, N2> getEdgesy() const {
		Bitmap2d<N1, N2 > dest;
		for (size_t y = 0; y < sizey(); ++y){
			for (size_t x = 1; x < sizex(); ++x) {
				if ( bmp1ds[x-1][y] != bmp1ds[x][y]) {
					dest.set(x, y);
				}
			}
		}
		return dest;
	}


	Bitmap2d<N1 * 2, N2> subdivx() const {
		Bitmap1dArray< N1 * 2, N2 > dest;
		for (size_t i = 0; i < bmp1ds.size(); ++i ) {
			dest[i] = bmp1ds[i].subdiv();
		}
		return Bitmap2d<N1 * 2, N2>(dest);
	}

	Bitmap2d& movex(const size_t size) {
		for (Bitmap1d<N1>& b : bmp1ds) {
			b.movex(size);
		}
		return *this;
	}

	Bitmap2d movedy(const size_t size) const {
		Bitmap1dArray<N1, N2> dest;
		for (size_t i = 0; i < N2 - size; ++i) {
			dest[i + size] = bmp1ds[i];
		}
		return Bitmap2d(dest);

	}

	Bitmap2d& movey(const size_t size) {
		*this = movedy(size);
		return (*this);
	}

private:
	Bitmap1dArray< N1, N2 > bmp1ds;
};

template<size_t N1, size_t N2, size_t N3>
using Bitmap2dArray = std::array < Bitmap2d<N1, N2>, N3 > ;


using Bitmap1x1 = Bitmap2d < 1, 1 >;
using Bitmap1x2 = Bitmap2d < 1, 2 >;
using Bitmap2x1 = Bitmap2d < 2, 1 >;
using Bitmap2x2 = Bitmap2d < 2, 2 >;
	}
}

#endif