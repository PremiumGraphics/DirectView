#ifndef __CRYSTAL_MATH_BITMAP_1D_H__
#define __CRYSTAL_MATH_BITMAP_1D_H__

#include <bitset>
#include <array>

namespace Crystal {
	namespace Math {

template<size_t N>
class Bitmap1d final
{
public:
	Bitmap1d()
	{}

	explicit Bitmap1d(const long v) :
		bits(v)
	{}

	explicit Bitmap1d(const std::bitset<N>& b) :
		bits(b)
	{}

	explicit Bitmap1d(const std::string& str) :
		bits(str)
	{}

	size_t count() const {
		return bits.count();
	}

	Bitmap1d<N>& set( const size_t i) {
		bits.set(i);
		return *(this);
	}

	Bitmap1d<N>& set() {
		bits.set();
		return (*this);
	}

	Bitmap1d<N>& reset(const size_t i) {
		bits.reset(i);
		return *(this);
	}

	Bitmap1d<N>& reset() {
		bits.reset();
		return *(this);
	}

	bool operator[](const size_t i) { return bits[i]; }

	bool operator[](const size_t i) const { return bits[i]; }

	Bitmap1d<N>& or(const Bitmap1d<N>& rhs) {
		bits |= rhs.bits;
		return *(this);
	}

	Bitmap1d<N>& and(const Bitmap1d<N>& rhs) {
		bits &= rhs.bits;
		return (*this);
	}

	size_t size() const { return bits.size(); }

	bool all() const { return bits.all(); }

	bool any() const { return bits.any(); }

	bool none() const { return bits.none(); }

	Bitmap1d<N> flip( const size_t i) {
		bits.flip(i);
		return (*this);
	}

	Bitmap1d<N>& flip() {
		bits.flip();
		return (*this);
	}

	std::string toString() const {
		return bits.to_string();
	}

	bool operator==(const Bitmap1d<N>& rhs) const {
		return bits == rhs.bits;
	}

	bool operator!=(const Bitmap1d<N>& rhs) const {
		return bits != rhs.bits;
	}

	Bitmap1d<N>& operator=(const Bitmap1d<N>& rhs) {
		bits = rhs.bits;
		return *this;
	}

private:
	std::bitset<N> bits;
};

template<size_t N1, size_t N2>
using Bitmap1dArray = std::array < Bitmap1d<N1>, N2 > ;
	}
}

#endif