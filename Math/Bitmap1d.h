#ifndef __CRYSTAL_MATH_BITMAP_1D_H__
#define __CRYSTAL_MATH_BITMAP_1D_H__

#include <bitset>

namespace Crystal {
	namespace Math {

template<size_t N>
using Bitmap1d = std::bitset <N> ;

template<size_t N>
class Bitmap1d_ final
{
public:
	Bitmap1d_()
	{}

	Bitmap1d_(const std::string& str) :
		bits(str)
	{}

	bool operator[](const size_t i) const { return bits[i]; }

	Bitmap1d_<N>& operator&=(const Bitmap1d_<N>& rhs) {
		bits &= rhs.bits;
		return (*this);
	}


private:
	std::bitset<N> bits;
};
	}
}

#endif