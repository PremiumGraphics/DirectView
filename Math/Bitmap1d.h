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

	Bitmap1d<N>& and(const Bitmap1d<N>& rhs) {
		bits &= rhs.bits;
		return (*this);
	}

	Bitmap1d<N>& or(const Bitmap1d<N>& rhs) {
		bits |= rhs.bits;
		return *(this);
	}

	Bitmap1d<N>& xor(const Bitmap1d<N>& rhs) {
		bits ^= rhs.bits;
		return (*this);
	}

	Bitmap1d<N> not() const {
		return Bitmap1d<N>( ~bits );
	}

	size_t size() const { return bits.size(); }

	bool isAll() const { return bits.all(); }

	bool isAny() const { return bits.any(); }

	bool isNone() const { return bits.none(); }

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

	Bitmap1d<N> getEdge() const {
		Bitmap1d<N> dest;
		for (size_t i = 1; i < bits.size(); ++i){
			if (!bits[i - 1] && bits[i]) {
				dest.set(i);
			}
		}
		return dest;
	}

private:
	std::bitset<N> bits;
};

template<size_t N1, size_t N2>
using Bitmap1dArray = std::array < Bitmap1d<N1>, N2 > ;
	}
}

#endif