#ifndef __CRYSTAL_MATH_BITMAP_H__
#define __CRYSTAL_MATH_BITMAP_H__

#include <bitset>
#include <vector>
#include <numeric>

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

	Bitmap1d& setAll() {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = true;
		}
		return (*this);
	}

	int getCount() const {
		return std::count(bits.begin(), bits.end(), true);
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

	std::bitset<2> to2Bit(const size_t i) const {
		std::bitset<2> b;
		b.set( bits[i] );
		b.set( bits[i+1] );
		return b;
	}

	std::vector< std::bitset<2> > to2Bits() const {
		std::vector< std::bitset<2> > b;
		for (size_t i = 1; i < bits.size(); ++i) {
			b.push_back(to2Bit(i));
		}
		return b;
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
		bmps(bmps)
	{}

	Bitmap2d(const size_t xSize, const size_t ySize) :
		bmps(ySize, Bitmap1d(xSize))
	{
	}

	size_t getSizeX() const { return bmps.front().size(); }

	size_t getSizeY() const { return bmps.size(); }

	Bitmap2d& setAll() {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].setAll();
		}
		return (*this);
	}


	Bitmap1d& operator[](const size_t i) { return bmps[i]; }

	bool get(const size_t x, const size_t y) const { return bmps[y][x]; }

	Bitmap2d& and(const Bitmap2d& rhs) {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].and(rhs.bmps[i]);
		}
		return (*this);
	}

	Bitmap2d& or(const Bitmap2d& rhs) {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].or(rhs.bmps[i]);
		}
		return (*this);
	}

	Bitmap2d& xor(const Bitmap2d& rhs) {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].xor(rhs.bmps[i]);
		}
		return (*this);
	}

	Bitmap2d not() {
		Bitmap1dVector bs;
		for (size_t i = 0; i < bmps.size(); ++i) {
			bs.push_back( bmps[i].not() );
		}
		return Bitmap2d(bs);
	}

	bool equals(const Bitmap2d& rhs) const {
		return bmps == rhs.bmps;
	}

	bool operator==(const Bitmap2d& rhs) const {
		return equals( rhs );
	}

	bool operator!=(const Bitmap2d& rhs) const {
		return !equals( rhs );
	}

	int getCount() const {
		int count = 0;
		for (const auto& b : bmps) {
			count += b.getCount();
		}
		return count;
	}

private:
	Bitmap1dVector bmps;
};

using Bitmap2dVector = std::vector < Bitmap2d > ;

class Bitmap3d final
{
public:
	explicit Bitmap3d(const Bitmap2dVector& bmps) :
	bmps(bmps)
	{
	}

	Bitmap3d(const unsigned int x, const unsigned int y, const unsigned int z):
		bmps( z, Bitmap2d(x,y) )
	{
	}

	unsigned int getSizeX() const {
		return bmps.front().getSizeX();
	}

	unsigned int getSizeY() const {
		return bmps.front().getSizeY();
	}

	unsigned int getSizeZ() const {
		return bmps.size();
	}

	Bitmap3d& setAll() {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].setAll();
		}
		return (*this);
	}

	bool get(const size_t x, const size_t y, const size_t z) const { return bmps[z].get(x,y); }

	Bitmap2d& operator[](const size_t i) { return bmps[i]; }

	Bitmap3d& and(const Bitmap3d& rhs) {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].and(rhs.bmps[i]);
		}
		return (*this);
	}

	Bitmap3d& or(const Bitmap3d& rhs) {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].or(rhs.bmps[i]);
		}
		return (*this);
	}

	Bitmap3d& xor(const Bitmap3d& rhs) {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].xor(rhs.bmps[i]);
		}
		return (*this);
	}

	Bitmap3d not() {
		Bitmap2dVector bs;
		for (size_t i = 0; i < bmps.size(); ++i) {
			bs.push_back(bmps[i].not());
		}
		return Bitmap3d(bs);
	}

	bool equals(const Bitmap3d& rhs) const {
		return bmps == rhs.bmps;
	}

	bool operator==(const Bitmap3d& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Bitmap3d& rhs) const {
		return !equals(rhs);
	}

	int getCount() const {
		int count = 0;
		for (const auto& b : bmps) {
			count += b.getCount();
		}
		return count;
	}


	//void set(const size_t i, const size_t j) { bmp2ds[i].set(j,k); }

	std::bitset<8> to8Bit(const size_t i, const size_t j, const size_t k) const {
		std::bitset<8> b;
		if (get(i,j,k))		{ b.set(0); }
		if (get(i+1,j,k))	{ b.set(1); }
		if (get(i+1,j+1,k))	{ b.set(2); }
		if (get(i,j+1,k))	{ b.set(3); }
		if (get(i,j,k+1))	{ b.set(4); }
		if (get(i+1,j,k+1))	{ b.set(5); }
		if (get(i+1,j+1,k+1)){ b.set(6); }
		if (get(i,j+1,k+1))	{ b.set(7); }

		/*
		Vector3d<T>(x1, y1, z1),
			Vector3d<T>(x2, y1, z1),
			Vector3d<T>(x2, y2, z1),
			Vector3d<T>(x1, y2, z1),
			Vector3d<T>(x1, y1, z2),
			Vector3d<T>(x2, y1, z2),
			Vector3d<T>(x2, y2, z2),
			Vector3d<T>(x1, y2, z2),
*/
		return b;

	}

private:
	Bitmap2dVector bmps;
};
	}
}

#endif