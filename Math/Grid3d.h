#ifndef __CRYSTAL_MATH_GRID_3D_H__
#define __CRYSTAL_MATH_GRID_3D_H__

#include "Grid2d.h"

namespace Crystal {
	namespace Math {

template< size_t N1, size_t N2, size_t N3, class T >
class Grid3d final
{
public:
	Grid3d() = default;

	Grid3d(const T v) {
		values.fill(v);
	}

	~Grid3d() = default;

	size_t size() const { return N1 * N2 * N3; }

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	size_t sizez() const { return N3; }

	T get(size_t i, size_t j, size_t k) const {
		return values[i][j][k];
	}

	void set(const size_t i, const size_t j, const size_t k, const T c) {
		values[i][j].set(k, c);
	}

	Grid2d<N1, N2, T>& operator[](size_t i) {
		return values[i];
	}

	const Grid2d<N1, N2, T> operator[](size_t i) const {
		return values[i];
	}

	bool equals(const Grid3d<N1, N2, N3, T>& rhs) const {
		return values == rhs.values;
	}

	bool operator==(const Grid3d<N1, N2, N3,T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Grid3d<N1, N2, N3,T>& rhs) const {
		return !equals(rhs);
	}


private:
	std::array< Grid2d<N1, N2, T>, N3 > values;
};

}
}

#endif