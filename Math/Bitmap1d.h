#ifndef __CRYSTAL_MATH_BITMAP_1D_H__
#define __CRYSTAL_MATH_BITMAP_1D_H__

#include <bitset>

namespace Crystal {
	namespace Math {

template<size_t N>
using Bitmap1d = std::bitset <N> ;
	}
}

#endif