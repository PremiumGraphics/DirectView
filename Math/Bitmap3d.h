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

	explicit Bitmap3d(const std::array<std::string, N3>& strs) {
		byStrings(strs);
	}

	size_t sizex() const {
		return bmp2ds.front().sizex();
	}

	size_t sizey() const {
		return bmp2ds.front().sizey();
	}

	size_t sizez() const {
		return bmp2ds.size();
	}

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


	//void set(const size_t x, const size_t y, const size_t z) { bmp2ds[x].set(y, z); }

	void set(const size_t x, const size_t y, const size_t z) { bmp2ds[z].set(x, y); }

	void reset(const size_t x, const size_t y, const size_t z) { bmp2ds[z].reset(x, y); }

	bool get(const size_t x, const size_t y, const size_t z) const { return bmp2ds[z].get(x, y); }

	//std::vector< Bitmap2d<N> > get2ds() const { return bmp2ds; }

	//bool get(const size_t x, const size_t y, const size_t z) { return bmp2ds[z].get(y,x) }

	Bitmap2d<N1, N2>& operator[](const std::size_t pos) { return bmp2ds[pos]; }

	Bitmap2d<N1,N2> operator[](const std::size_t pos) const { return bmp2ds[pos]; }

	std::string toString() const {
		std::string str;
		for (const auto& b : bmp2ds) {
			str += b.toString();
		}
		return str;
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

	/*
	void byString(const std::string& str) {
		assert(str.size() == this->size());
		for (size_t i = 0; i < N2; ++i) {
			const size_t start = i * N;
			const size_t end = (i + 1) * N1;
			const auto s = str.substr(start, end);
			bmp1ds[i] = Bitmap2d<N1,N2>(s);
		}
	}
	*/

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
			bmp1ds[i].and(rhs.bmp2ds[i]);
		}
		return (*this);
	}
	/*
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
		Bitmap1dArray<N1, N2> bs = bmp1ds;
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bs[i] = bmp1ds[i].not();
		}
		return Bitmap2d<N1, N2>(bs);
	}
	*/

private:
	Bitmap2dArray<N1, N2, N3> bmp2ds;
};

	}
}

#endif