#ifndef __CRYSTAL_MATH_GRID_2D_H__
#define __CRYSTAL_MATH_GRID_2D_H__

#include "Grid1d.h"

namespace Crystal {
	namespace Math {

template< size_t N1, size_t N2, class T >
class Grid2d final
{
public:
	Grid2d() = default;

	Grid2d(const T v) {
		values.fill(v);
	}

	~Grid2d() = default;

	size_t size() const { return N1 * N2; }

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	T get(size_t i, size_t j) const {
		return values[i][j];
	}

	Grid1d<N1, T> get(size_t i) const {
		return values[i];
	}

	void set(const size_t i, const size_t j, const T& c) {
		values[i].set(j, c);
	}

	void set(const size_t i, const Grid2d<N1,N2,T>& values1d) {
		values[i] = values1d;
	}

	Grid1d<N1, T> operator[](size_t i) const {
		return values[i];
	}

	Grid1d<N1, T>& operator[](const size_t i) {
		return values[i];
	}

	bool equals(const Grid2d<N1, N2, T>& rhs) const {
		return values == rhs.values;
	}

	bool operator==(const Grid2d<N1, N2, T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Grid2d<N1, N2, T>& rhs) const {
		return !equals(rhs);
	}

private:
	std::array< Grid1d<N1, T>, N2 > values;
};

	}
}

#endif