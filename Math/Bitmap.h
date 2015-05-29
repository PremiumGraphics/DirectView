#ifndef __CRYSTAL_MATH_BITMAP_H__
#define __CRYSTAL_MATH_BITMAP_H__

#include <bitset>
#include <vector>

namespace Crystal {
	namespace Math {

class Bitmap1d final
{
public:
	Bitmap1d()
	{}

	explicit Bitmap1d(const size_t size) :
		bits(size)
	{}

	explicit Bitmap1d(const std::vector<bool>& b) :
		bits(b)
	{}

	Bitmap1d& set( const size_t i) {
		bits[i] = true;
		return *(this);
	}

	Bitmap1d& set() {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = true;
		}
		return (*this);
	}

	bool operator[](const size_t i) const { return bits[i]; }

	Bitmap1d& and(const Bitmap1d& rhs) {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = bits[i] & rhs.bits[i];
		}
		return (*this);
	}

	Bitmap1d& or(const Bitmap1d& rhs) {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = bits[i] | rhs.bits[i];
		}
		return *(this);
	}

	Bitmap1d& xor(const Bitmap1d& rhs) {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = bits[i] ^ rhs.bits[i];
		}
		return *(this);
	}

	Bitmap1d not() {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = !bits[i];
		}
		return *(this);
	}

	size_t size() const { return bits.size(); }

	/*
	bool isAll() const { return bits.all(); }

	bool isAny() const { return bits.any(); }

	bool isNone() const { return bits.none(); }
	*/

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

private:
	//std::bitset<SIZE> bits;
	std::vector<bool> bits;	// not best practice. see Effective STL.

};

using Bitmap1dVector = std::vector < Bitmap1d >;

class Bitmap2d final
{
public:
	Bitmap2d() = default;

	explicit Bitmap2d(const Bitmap1dVector& bmps) :
		bmp1ds(bmps)
	{}

	Bitmap2d(const size_t xSize, const size_t ySize)
	{
		for (size_t i = 0; i < ySize; ++i) {
			bmp1ds.push_back(Bitmap1d(xSize));
		}
	}

	size_t getSizeX() const { return bmp1ds.front().size(); }

	size_t getSizeY() const { return bmp1ds.size(); }

	Bitmap1d operator[](const size_t i) const { return bmp1ds[i]; }

	Bitmap1d& operator[](const size_t i) { return bmp1ds[i]; }

	Bitmap2d& and(const Bitmap2d& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].and(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d& or(const Bitmap2d& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].or(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d& xor(const Bitmap2d& rhs) {
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bmp1ds[i].xor(rhs.bmp1ds[i]);
		}
		return (*this);
	}

	Bitmap2d not() {
		Bitmap1dVector bs;
		for (size_t i = 0; i < bmp1ds.size(); ++i) {
			bs.push_back( bmp1ds[i].not() );
		}
		return Bitmap2d(bs);
	}

private:
	Bitmap1dVector bmp1ds;
};

using Bitmap2dVector = std::vector < Bitmap2d > ;

class Bitmap3d final
{
public:
	explicit Bitmap3d(const Bitmap2dVector& bmps) :
	bmp2ds(bmps)
	{
	}

	Bitmap3d(const unsigned int x, const unsigned int y, const unsigned int z) {
		for (size_t i = 0; i < z; ++i) {
			for (size_t i = 0; i < z; ++i) {
				bmp2ds.push_back(Bitmap2d(x,y));
			}
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

	Bitmap3d not() {
		Bitmap2dVector bs;
		for (size_t i = 0; i < bmp2ds.size(); ++i) {
			bs.push_back( bmp2ds[i].not() );
		}
		return Bitmap3d(bs);
	}

	//bool get(const size_t i, const size_t j, const size_t k) const { return bmp2ds[i].get(j,k); }
	Bitmap2d operator[](const size_t i) const { return bmp2ds[i]; }

	Bitmap2d& operator[](const size_t i) { return bmp2ds[i]; }



	//void set(const size_t i, const size_t j) { bmp2ds[i].set(j,k); }

	std::bitset<8> to8Bit(const size_t i, const size_t j, const size_t k) const {
		std::bitset<8> b;
		if (bmp2ds[i][j][k]){ b.set(0);}
		if (bmp2ds[i][j][k]){ b.set(1); }
		if (bmp2ds[i][j+1][k]) { b.set(2); }
		if (bmp2ds[i][j+1][k+1]) { b.set(3); }
		if (bmp2ds[i+1][j][k])	{ b.set(4); }
		if (bmp2ds[i+1][j][k+1]) { b.set(5); }
		if (bmp2ds[i+1][j+1][k]) { b.set(6); }
		if (bmp2ds[i+1][j+1][k+1]) { b.set(7); }
		return b;

	}

private:
	Bitmap2dVector bmp2ds;
};
	}
}

#endif