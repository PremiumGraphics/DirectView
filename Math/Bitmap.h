#ifndef __CRYSTAL_MATH_BITMAP_1D_H__
#define __CRYSTAL_MATH_BITMAP_1D_H__

#include <bitset>
#include <array>

namespace Crystal {
	namespace Math {

template<size_t SIZE = 32>
class Bitmap final
{
public:
	Bitmap()
	{}

	explicit Bitmap(const std::bitset<SIZE>& b) :
		bits(b)
	{}

	explicit Bitmap(const std::string& str) :
		bits(str)
	{}

	explicit Bitmap(const unsigned long v) :
		bits(v)
	{}

	size_t count() const {
		return bits.count();
	}

	Bitmap& set( const size_t i) {
		bits.set(i);
		return *(this);
	}

	Bitmap& set() {
		bits.set();
		return (*this);
	}

	Bitmap& reset(const size_t i) {
		bits.reset(i);
		return *(this);
	}

	Bitmap& reset() {
		bits.reset();
		return *(this);
	}

	bool operator[](const size_t i) { return bits[i]; }

	bool operator[](const size_t i) const { return bits[i]; }

	bool get(const size_t i) const { return bits[i]; }

	Bitmap& movex(const size_t size) {
		bits <<= size;
		return (*this);
	}

	Bitmap& operator<<=(const size_t size) {
		bits <<= size;
		return (*this);
	}

	Bitmap& and(const Bitmap& rhs) {
		bits &= rhs.bits;
		return (*this);
	}

	Bitmap& or(const Bitmap& rhs) {
		bits |= rhs.bits;
		return *(this);
	}

	Bitmap& xor(const Bitmap& rhs) {
		bits ^= rhs.bits;
		return (*this);
	}

	Bitmap not() const {
		return Bitmap( ~bits );
	}

	size_t size() const { return bits.size(); }

	bool isAll() const { return bits.all(); }

	bool isAny() const { return bits.any(); }

	bool isNone() const { return bits.none(); }

	std::string toString() const {
		return bits.to_string();
	}

	bool operator==(const Bitmap& rhs) const {
		return bits == rhs.bits;
	}

	bool operator!=(const Bitmap& rhs) const {
		return bits != rhs.bits;
	}

	Bitmap& operator=(const Bitmap& rhs) {
		bits = rhs.bits;
		return *this;
	}

	unsigned long toULong() const {
		return bits.to_ulong();
	}

private:
	std::bitset<SIZE> bits;
};

	}
}

#endif