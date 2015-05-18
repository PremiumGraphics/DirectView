#ifndef __CRYSTAL_MATH_BITMAP_3D_H__
#define __CRYSTAL_MATH_BITMAP_3D_H__

#include "Bitmap2d.h"

#include <array>

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2, size_t N3>
class Bitmap3d final
{
public:
	Bitmap3d()
	{}

	explicit Bitmap3d(const size_t size2d) {
		bmp2ds.fill(size2d);
	}

	explicit Bitmap3d(const std::array< Bitmap2d<N1, N2>, N3 >& bmps) :
		bmp2ds( bmps )
	{
	}

	explicit Bitmap3d(const std::string& str) {
		byString(str);
	}

	explicit Bitmap3d(const std::array<std::string, N3>& strs) {
		byStrings(strs);
	}

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	size_t sizez() const { return N3; }

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

	bool isNone() const {
		for (const auto& b : bmp2ds) {
			if (!b.isNone()) {
				return false;
			}
		}
		return true;
	}


	void set(const size_t x, const size_t y, const size_t z) { bmp2ds[z].set(x, y); }

	void reset(const size_t x, const size_t y, const size_t z) { bmp2ds[z].reset(x, y); }

	bool get(const size_t x, const size_t y, const size_t z) const { return bmp2ds[z].get(x, y); }

	Bitmap2d<N1, N2>& operator[](const std::size_t pos) { return bmp2ds[pos]; }

	Bitmap2d<N1,N2> operator[](const std::size_t pos) const { return bmp2ds[pos]; }

	std::string toString() const {
		std::string str;
		for (const auto& b : bmp2ds) {
			str += b.toString();
		}
		return str;
	}

	bool isAll() const {
		return count() == size();
	}

	bool equals(const Bitmap3d<N1,N2,N3>& rhs) const {
		return bmp2ds == rhs.bmp2ds;
	}

	bool operator==(const Bitmap3d<N1, N2, N3>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Bitmap3d<N1, N2, N3>& rhs) const {
		return !equals(rhs);
	}

	void byString(const std::string& str) {
		assert(str.size() == this->size());
		std::array< std::string, N3 > strs;
		for (size_t i = 0; i < N3; ++i) {
			const size_t start = i * N1 * N2;
			const size_t len = N1 * N2;
			strs[i] = str.substr(start, len);
		}
		byStrings(strs);
	}

	void byStrings(const std::array< std::array<std::string, N2>, N3 >& strs) {
		for (size_t i = 0; i < N3; ++i) {
			bmp2ds[i] = Bitmap2d<N1, N2>(strs[i]);
		}
	}
	
	void byStrings(const std::array<std::string, N3>& strs) {
		for (size_t i = 0; i < N3; ++i) {
			bmp2ds[i] = Bitmap2d<N1,N2>(strs[i]);
		}
	}

	Bitmap3d<N1, N2, N3>& and(const Bitmap3d<N1, N2, N3>& rhs) {
		for (size_t i = 0; i < bmp2ds.size(); ++i) {
			bmp2ds[i].and(rhs.bmp2ds[i]);
		}
		return (*this);
	}

	Bitmap3d<N1, N2, N3>& or(const Bitmap3d<N1, N2, N3>& rhs) {
		for (size_t i = 0; i < bmp2ds.size(); ++i) {
			bmp2ds[i].or(rhs.bmp2ds[i]);
		}
		return (*this);
	}

	Bitmap3d<N1, N2, N3>& xor(const Bitmap3d<N1, N2, N3>& rhs) {
		for (size_t i = 0; i < bmp2ds.size(); ++i) {
			bmp2ds[i].xor(rhs.bmp2ds[i]);
		}
		return (*this);
	}

	Bitmap3d<N1, N2, N3> not() const {
		Bitmap2dArray<N1, N2, N3> bs;
		for (size_t i = 0; i < bmp2ds.size(); ++i) {
			bs[i] = bmp2ds[i].not();
		}
		return Bitmap3d<N1, N2, N3>(bs);
	}

	Bitmap3d& movex(const size_t size) {
		for (Bitmap2d<N1,N2>& b : bmp2ds) {
			b.movex(size);
		}
		return *this;
	}


private:
	Bitmap2dArray<N1, N2, N3> bmp2ds;
};

using Bitmap1x1x1 = Bitmap3d < 1, 1, 1 >;
using Bitmap1x1x2 = Bitmap3d < 1, 1, 2 >;
using Bitmap1x2x4 = Bitmap3d < 1, 2, 4 >;
using Bitmap2x2x2 = Bitmap3d < 2, 2, 2 >;

	}
}

#endif