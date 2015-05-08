#ifndef __CRYSTAL_MATH_GRID_1D_H__
#define __CRYSTAL_MATH_GRID_1D_H__

#include <array>

namespace Crystal {
	namespace Math {

template< size_t N, class T >
class Grid1d final
{
public:
	Grid1d() = default;

	Grid1d(const T& v) {
		values.fill(v);
	}

	~Grid1d() = default;

	size_t size() const { return N; }

	T operator[](size_t i) const {
		return values[i];
	}

	T& operator[](size_t i) {
		return values[i];
	}

	T get(const size_t i) {
		return values[i];
	}

	void set(const size_t i, const T& c) {
		values[i] = c;
	}

	bool equals(const Grid1d<N,T>& rhs) const {
		return values == rhs.values;
	}

	bool operator==(const Grid1d<N, T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Grid1d<N, T>& rhs) const {
		return !equals(rhs);
	}

private:
	std::array< T, N > values;

};

	}
}

#endif