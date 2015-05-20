#ifndef __CRYSTAL_MATH_DYNAMIC_BITMAP_H__
#define __CRYSTAL_MATH_DYNAMIC_BITMAP_H__

#include <algorithm>

#include <array>
#include <bitset>

namespace Crystal {
	namespace Math {

template<size_t DIM, size_t BITS_PER_BLOCK = 32>
class DynamicBitmap final
{
public:
	DynamicBitmap() = default;

	DynamicBitmap(std::vector<std::bitset<BITS_PER_BLOCK> >& bits) :
		bits(bits)
	{}

	DynamicBitmap(const size_t size) {
		const auto s = size / BITS_PER_BLOCK + 1;
		bits.resize(s);
	}

	~DynamicBitmap() = default;


private:
	std::vector< std::bitset<BITS_PER_BLOCK> > bits;
};
	}
}

#endif