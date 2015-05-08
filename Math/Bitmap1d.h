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

	Bitmap1d_(const Bitmap1d<N>& b) :
		bits(b)
	{}

	Bitmap1d_(const std::string& str) :
		bits(str)
	{}

	size_t count() const {
		return bits.count();
	}

	Bitmap1d_<N>& set( const size_t i) {
		bits.set(i);
		return *(this);
	}

	Bitmap1d_<N>& set() {
		bits.set();
		return (*this);
	}

	Bitmap1d_<N>& reset(const size_t i) {
		bits.reset(i);
		return *(this);
	}

	Bitmap1d_<N>& reset() {
		bits.reset();
		return *(this);
	}

	bool operator[](const size_t i) const { return bits[i]; }

	Bitmap1d_<N>& operator&=(const Bitmap1d_<N>& rhs) {
		bits &= rhs.bits;
		return (*this);
	}

	size_t size() const { return bits.size(); }

	bool all() const { return bits.all(); }

	bool any() const { return bits.any(); }

	bool none() const { return bits.none(); }

	Bitmap1d_<N> flip( const size_t i) {
		bits.flip(i);
		return (*this);
	}

	Bitmap1d_<N> flip() {
		bits.flip();
		return (*this);
	}

	std::string toString() const {
		return bits.to_string();
	}

	bool operator==(const Bitmap1d_<N>& rhs) const {
		return bits == rhs.bits;
	}

	bool operator!=(const Bitmap1d_<N>& rhs) const {
		return bits != rhs.bits;
	}


private:
	std::bitset<N> bits;
};
	}
}

#endif