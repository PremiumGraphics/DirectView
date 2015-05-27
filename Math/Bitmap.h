#ifndef __CRYSTAL_MATH_BITMAP_H__
#define __CRYSTAL_MATH_BITMAP_H__

#include <bitset>
#include <vector>

namespace Crystal {
	namespace Math {

template<size_t SIZE = 32>
class Bitmap1d final
{
public:
	Bitmap1d()
	{}

	explicit Bitmap1d(const std::bitset<SIZE>& b) :
		bits(b)
	{}

	explicit Bitmap1d(const std::string& str) :
		bits(str)
	{}

	explicit Bitmap1d(const unsigned long v) :
		bits(v)
	{}

	size_t count() const {
		return bits.count();
	}

	Bitmap1d& set( const size_t i) {
		bits.set(i);
		return *(this);
	}

	Bitmap1d& set() {
		bits.set();
		return (*this);
	}

	Bitmap1d& reset(const size_t i) {
		bits.reset(i);
		return *(this);
	}

	Bitmap1d& reset() {
		bits.reset();
		return *(this);
	}

	bool operator[](const size_t i) { return bits[i]; }

	bool operator[](const size_t i) const { return bits[i]; }

	bool get(const size_t i) const { return bits[i]; }

	Bitmap1d& movex(const size_t size) {
		bits <<= size;
		return (*this);
	}

	Bitmap1d& operator<<=(const size_t size) {
		bits <<= size;
		return (*this);
	}

	Bitmap1d& and(const Bitmap1d& rhs) {
		bits &= rhs.bits;
		return (*this);
	}

	Bitmap1d& or(const Bitmap1d& rhs) {
		bits |= rhs.bits;
		return *(this);
	}

	Bitmap1d& xor(const Bitmap1d& rhs) {
		bits ^= rhs.bits;
		return (*this);
	}

	Bitmap1d not() const {
		return Bitmap1d( ~bits );
	}

	size_t size() const { return bits.size(); }

	bool isAll() const { return bits.all(); }

	bool isAny() const { return bits.any(); }

	bool isNone() const { return bits.none(); }

	std::string toString() const {
		return bits.to_string();
	}

	bool operator==(const Bitmap1d& rhs) const {
		return bits == rhs.bits;
	}

	bool operator!=(const Bitmap1d& rhs) const {
		return bits != rhs.bits;
	}

	Bitmap1d& operator=(const Bitmap1d& rhs) {
		bits = rhs.bits;
		return *this;
	}

	unsigned long toULong() const {
		return bits.to_ulong();
	}

private:
	std::bitset<SIZE> bits;
};

//template <size_t SIZE >
//using Bitmap2d = std::vector < std::vector< Bitmap1d<SIZE > > > ;

template<size_t SIZE>
class Bitmap2d final
{
public:
	Bitmap2d() = default;

	Bitmap2d(const size_t ySize) :
		bmp1ds(ySize)
	{}

	size_t sizex() const { return SIZE; }

	size_t sizey() const { return bmp1ds.size(); }


	size_t count() const {
		auto howMany = 0;
		for (const auto& b : bmp1ds) {
			howMany += b.count();
		}
		return howMany;
	}

	bool isAll() const {
		return count() == size();
	}

	Bitmap2d<SIZE>& and(const Bitmap2d<SIZE>& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].and(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d<SIZE>& or(const Bitmap2d<SIZE>& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].or(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d<SIZE>& xor(const Bitmap2d<SIZE>& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].xor(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d<SIZE> not() const {
		std::vector< Bitmap1d< SIZE > > bs;
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bs[i] = bmp1ds[i].not();
		}
		return Bitmap2d<SIZE>(bs);
	}

private:
	std::vector< Bitmap1d< SIZE > > bmp1ds;
};

//template< size_t SIZE >
//using Bitmap3d = std::vector < std::vector< Bitmap2d<SIZE> > > ;

template<size_t SIZE>
class Bitmap3d final
{
public:
	/**
	Bitmap3d(const unsigned int y, const unsigned int z) {
		bmp.resize(y);
	}
	*/

	unsigned int getSizeX() const {
		return SIZE;
	}

	unsigned int getSizeY() const {
		return bmp.size();
	}

	unsigned int getSizeZ() const {
		return bmp.front().size();
	}


	std::bitset<8> to8Bits() const {
		std::vector< std::bitset<8> > bits;
		for (size_t i = 0; i < getSizeX()-1; ++i ) {
			for (size_t j = 0; j < getSizeY()-1; ++j) {
				for (size_t k = 0; l < getSizeZ()-1; ++k) {
					std::bitset<8> b;
					if (bmp[i][j][k]) { b.set(0); }
					if (bmp[i][j][k+1]) { b.set(1); }
					if (bmp[i][j+1][k]) { b.set(2); }
					if (bmp[i][j+1][k+1]) { b.set(3); }
					if (bmp[i+1][j][k]) { b.set(4); }
					if (bmp[i+1][j][k+1]) { b.set(5); }
					if (bmp[i+1][j+1][k]) { b.set(6); }
					if (bmp[i+1][j+1][k+1]) { b.set(7); }
					bits.push_back(b);
				}
			}
		}
		return bits;
	}
private:
	std::vector < std::vector < Bitmap1d<SIZE> > > bmp;
};
	}
}

#endif