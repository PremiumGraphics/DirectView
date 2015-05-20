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

	explicit Bitmap1d(const std::bitset<N>& b) :
		bits(b)
	{}

	explicit Bitmap1d(const std::string& str) :
		bits(str)
	{}

	explicit Bitmap1d(const unsigned long v) :
		bits(v)
	{}

	explicit Bitmap1d(const Bitmap1d<N/2>& b1, const Bitmap1d<N/2>& b2)
	{
		for (size_t i = 0; i < b2.size(); ++i) {
			bits[i] = b2.get(i);
		}
		const auto size = b2.size();
		for (size_t i = 0; i < b1.size(); ++i) {
			bits[size + i] = b1.get(i);
		}
	}

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

	bool get(const size_t i) const { return bits[i]; }

	Bitmap1d<N>& movex(const size_t size) {
		bits <<= size;
		return (*this);
	}

	Bitmap1d<N>& operator<<=(const size_t size) {
		bits <<= size;
		return (*this);
	}

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
			if ( bits[i - 1] != bits[i]) {
				dest.set(i);
			}
		}
		return dest;
	}

	Bitmap1d<N*2> subdiv() const {
		std::bitset<N * 2> dest;
		for (size_t i = 0; i < bits.size(); ++i) {
			dest[i*2] = bits[i];
			dest[i*2+1] = bits[i];
		}
		return Bitmap1d<N * 2>(dest);
	}

	unsigned long toULong() const {
		return bits.to_ulong();
	}

private:
	std::bitset<N> bits;
};

template<size_t N1, size_t N2>
using Bitmap1dArray = std::array < Bitmap1d<N1>, N2 > ;

using Bitmap1 = Bitmap1d < 1 >;
using Bitmap2 = Bitmap1d < 2 >;
using Bitmap4 = Bitmap1d < 4 >;
using Bitmap8 = Bitmap1d < 8 >;
using Bitmap16 = Bitmap1d < 16 >;
using Bitmap32 = Bitmap1d < 32 >;
using Bitmap64 = Bitmap1d < 64 >;
using Bitmap128 = Bitmap1d < 128 >;
using Bitmap256 = Bitmap1d < 256 >;
using Bitmap512 = Bitmap1d < 512 >;
using Bitmap1024 = Bitmap1d < 1024 >;

	}
}

#endif