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

	size_t getCount() const {
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
	bool get(const size_t i) const { return bits[i]; }

	Bitmap1d& movex(const size_t size) {
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

template <size_t SIZE >
using Bitmap1dVector = std::vector < Bitmap1d<SIZE > >;

template<size_t SIZE>
class Bitmap2d final
{
public:
	Bitmap2d() = default;

	explicit Bitmap2d(const Bitmap1dVector<SIZE>& bmps) :
		bmp1ds(bmps)
	{}

	explicit Bitmap2d(const size_t ySize) :
		bmp1ds(ySize)
	{}

	explicit Bitmap2d(const size_t ySize, const std::string& str)
	{
		byString(str);
	}


	size_t getSizeX() const { return SIZE; }

	size_t getSizeY() const { return bmp1ds.size(); }

	size_t getTotalSize() const { return getSizeX() * getSizeY(); }

	bool get(const size_t i,const size_t j) const { return bmp1ds[i].get(j); }

	void set(const size_t i, const size_t j) { bmp1ds[i].set(j); }

	Bitmap2d& operator[](const size_t i) { return bmp1ds[i]; }

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
			bs.push_back( bmp1ds[i].not() );
		}
		return Bitmap2d<SIZE>(bs);
	}

	void byString(const std::string& str, const size_t ySize) {
		std::vector< std::string > strs;
		for (size_t i = 0; i < ySize; ++i) {
			const size_t start = i * getSizeX();
			const size_t len = getSizeX();
			strs.push_back( str.substr(start, len) );
		}
		byStrings(strs);
	}

	void byStrings(const std::vector<std::string>& strs) {
		for (size_t i = 0; i < strs.size(); ++i) {
			bmp1ds.push_back( Bitmap1d<SIZE>(strs[i]) );
		}
	}

private:
	Bitmap1dVector< SIZE > bmp1ds;
};

template< size_t SIZE >
using Bitmap2dVector = std::vector < Bitmap2d<SIZE> > ;

template<size_t SIZE>
class Bitmap3d final
{
public:
	explicit Bitmap3d(const Bitmap2dVector<SIZE>& bmps) :
	bmp2ds(bmps)
	{
	}

	Bitmap3d(const unsigned int y, const unsigned int z) {
		for (size_t i = 0; i < z; ++i) {
			bmp2ds.push_back(Bitmap2d<SIZE>(y));
		}
	}

	unsigned int getSizeX() const {
		return bmp2ds.front().getSizeX();
	}

	unsigned int getSizeY() const {
		return bmp2ds.front().getSizeY();
	}

	unsigned int getSizeZ() const {
		return bmp2ds.size();
	}

	Bitmap3d<SIZE> not() const {
		Bitmap2dVector< SIZE > bs;
		for (size_t i = 0; i < bmp2ds.size(); ++i) {
			bs.push_back( bmp2ds[i].not() );
		}
		return Bitmap3d<SIZE>(bs);
	}

	bool get(const size_t i, const size_t j, const size_t k) const { return bmp2ds[i].get(j,k); }

	void set(const size_t i, const size_t j) { bmp2ds[i].set(j,k); }

	std::bitset<8> to8Bit(const size_t i, const size_t j, const size_t k) const {
		std::bitset<8> b;
		if (get(i, j, k)){ b.set(0);}
		if (get(i, j, k + 1)){ b.set(1); }
		if (get(i, j + 1, k)) { b.set(2); }
		if (get(i, j + 1, k + 1)) { b.set(3); }
		if (get(i + 1, j, k))	{ b.set(4); }
		if (get(i + 1, j, k + 1)) { b.set(5); }
		if (get(i + 1, j + 1, k)) { b.set(6); }
		if (get(i + 1, j + 1, k + 1)) { b.set(7); }
		return b;

	}

private:
	Bitmap2dVector<SIZE> bmp2ds;
};
	}
}

#endif