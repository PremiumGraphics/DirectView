#ifndef __CRYSTAL_MATH_BITMAP_H__
#define __CRYSTAL_MATH_BITMAP_H__

#include <bitset>
#include <vector>
#include <array>
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

	Bitmap1d& set( const size_t i, const bool b = true) {
		bits[i] = b;
		return *(this);
	}

	Bitmap1d& setAll(const bool b = true) {
		for (size_t i = 0; i < bits.size(); ++i) {
			bits[i] = b;
		}
		return (*this);
	}

	int getCount() const {
		return std::count(bits.begin(), bits.end(), true);
	}

	bool operator[](const size_t i) const { return bits[i]; }

	bool get(const size_t i) const { return bits[i]; }

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

	size_t getSize() const { return bits.size(); }

	bool isAll() const { return getCount() == getSize(); }

	bool isAny() const { return !isNone(); }

	bool isNone() const { return getCount() == 0; }

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

	Bitmap1d getSub(const size_t startIndex, const size_t endIndex) const {
		std::vector<bool> bs(bits.begin() + startIndex, bits.begin() + endIndex);
		return Bitmap1d( bs );
	}

	Bitmap1d& set(const unsigned int start, const Bitmap1d& rhs) {
		for (size_t x = 0; x < rhs.getSize(); ++x) {
			const bool b = rhs.get(x);
			set(x + start, b);
		}
		return (*this);
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

	Bitmap2d(const size_t xSize, const size_t ySize, const bool b) :
		bmps(ySize, Bitmap1d(xSize))
	{
		for (auto& bm : bmps) {
			bm.setAll(b);
		}
	}

	size_t getSizeX() const { return bmps.front().getSize(); }

	size_t getSizeY() const { return bmps.size(); }

	size_t getSize() const { return getSizeX() * getSizeY(); }

	Bitmap2d& setAll() {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].setAll();
		}
		return (*this);
	}

	bool get(const size_t x, const size_t y) const { return bmps[y][x]; }

	bool isAll() const { return getCount() == getSize(); }

	bool isAny() const { return !isNone(); }

	bool isNone() const { return getCount() == 0; }

	Bitmap1d& get(const size_t y) {
		return bmps[y];
	}

	Bitmap2d& set(const size_t x, const size_t y, const bool b = true) {
		bmps[y].set(x, b);
		return (*this);
	}

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

	Bitmap2d getSub(const size_t startx, const size_t endx, const size_t starty, const size_t endy) const {
		Bitmap1dVector bs( bmps.begin() + starty, bmps.begin() + endy );
		for (auto& bm : bs) {
			bm = bm.getSub(startx, endx);
		}
		return Bitmap2d(bs);
	}

	Bitmap2d& set(const std::array<unsigned int, 2>& start, const Bitmap2d& rhs) {
		for (size_t x = 0; x < rhs.getSizeX(); ++x) {
			for (size_t y = 0; y < rhs.getSizeY(); ++y) {
				const bool b = rhs.get(x, y);
				set(x + start[0], y + start[1], b);
			}
		}
		return (*this);
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

	Bitmap3d(const size_t xSize, const size_t ySize, const size_t zSize, const bool b) :
		bmps(zSize, Bitmap2d(xSize, ySize, b))
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

	unsigned int getSize() const {
		return getSizeX() * getSizeY() * getSizeZ();
	}

	std::array<unsigned int, 3> getSizes() const {
		return { getSizeX(), getSizeY(), getSizeZ() };
	}

	bool isAll() const { return getCount() == getSize(); }

	bool isAny() const { return !isNone(); }

	bool isNone() const { return getCount() == 0; }


	Bitmap3d& setAll() {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].setAll();
		}
		return (*this);
	}

	bool get(const size_t x, const size_t y, const size_t z) const { return bmps[z].get(x,y); }

	void set(const size_t x, const size_t y, const size_t z, const bool b = true) { bmps[z].set(x, y, b); }

	//Bitmap2d& operator[](const size_t i) { return bmps[i]; }

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

		return b;
	}

	Bitmap3d getSub(const std::array<unsigned int, 3>& start, const std::array<unsigned int, 3>& end) const {
		Bitmap2dVector bs(bmps.begin() + start[2], bmps.begin() + end[2]);
		for (auto& bm : bs) {
			bm = bm.getSub(start[0], end[0], start[1], end[1]);
		}
		return Bitmap3d(bs);
	}

	Bitmap3d& set(const std::array<unsigned int, 3>& start, const Bitmap3d& rhs) {
		for (size_t x = 0; x < rhs.getSizeX(); ++x) {
			for (size_t y = 0; y < rhs.getSizeY(); ++y) {
				for (size_t z = 0; z < rhs.getSizeZ(); ++z) {
					const bool b = rhs.get(x, y, z);
					set(x + start[0], y + start[1], z + start[2], b);
				}
			}
		}
		return (*this);
	}

private:
	Bitmap2dVector bmps;
};
	}
}

#endif