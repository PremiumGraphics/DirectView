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

	Bitmap2d(const size_t xSize, const size_t ySize)
	{
		for (size_t i = 0; i < ySize; ++i) {
			bmps.push_back(Bitmap1d(xSize));
		}
	}

	size_t getSizeX() const { return bmps.front().size(); }

	size_t getSizeY() const { return bmps.size(); }

	Bitmap2d& setAll() {
		for (size_t i = 0; i < bmps.size(); ++i) {
			bmps[i].setAll();
		}
		return (*this);
	}


	Bitmap1d operator[](const size_t i) const { return bmps[i]; }

	Bitmap1d& operator[](const size_t i) { return bmps[i]; }

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

	/*
	Bitmap2d& setCircle() {
		//const Vector3d<float> center(getSizeX() / 2.0f - 0.5f, getSizeY() / 2.0f - 0.5f, 0.0);
		const int centerX = getSizeX() / 2;
		const int centerY = getSizeY() / 2;
		const int radius = getSizeX() / 2;
		for (size_t x = 0; x < getSizeX(); ++x) {
			for (size_t y = 0; y < getSizeY(); ++y) {
				if (std::pow(centerX - x, 2) * std::pow(centerY - y, 2) <= radius * radius) {
					bmps[x].set(y);
				}
			}
		}
		return (*this);
	}
	*/

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

	Bitmap3d(const unsigned int x, const unsigned int y, const unsigned int z) {
		for (size_t i = 0; i < z; ++i) {
			bmps.push_back(Bitmap2d(x, y));
		}
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

	//bool get(const size_t i, const size_t j, const size_t k) const { return bmp2ds[i].get(j,k); }
	Bitmap2d operator[](const size_t i) const { return bmps[i]; }

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

	/*
	Bitmap3d& setSphere() {
		const Vector3d<float> center(getSizeX() / 2.0f, getSizeY() / 2.0f, getSizeZ()/2.0f);
		const float radius = getSizeX() / 2.0f;
		for (size_t x = 0; x < getSizeX(); ++x) {
			for (size_t y = 0; y < getSizeY(); ++y) {
				for (size_t z = 0; z < getSizeZ(); ++z) {
					const Vector3d<float> pos(x+0.5f, y+0.5f, z+0.5f);
					if (pos.getDistanceSquared(center) < radius * radius) {
						bmps[x][y].set(z);
					}
				}
			}
		}
		return (*this);
	}
	*/

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
		if (bmps[i][j][k])		{ b.set(0); }
		if (bmps[i+1][j][k])	{ b.set(1); }
		if (bmps[i+1][j+1][k])	{ b.set(2); }
		if (bmps[i][j+1][k])	{ b.set(3); }
		if (bmps[i][j][k+1])	{ b.set(4); }
		if (bmps[i+1][j][k+1])	{ b.set(5); }
		if (bmps[i+1][j+1][k+1]){ b.set(6); }
		if (bmps[i][j+1][k+1])	{ b.set(7); }

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