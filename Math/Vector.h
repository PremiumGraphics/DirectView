#ifndef __CRYSTAL_MATH_VECTOR_H__
#define __CRYSTAL_MATH_VECTOR_H__

#include <array>

namespace Crystal {
	namespace Math {

template< typename T, size_t DIM >
class Vector final
{
public:
	Vector()
	{
		v.fill(0);
	}

	template<size_t I>
	void set(const T v) {
		static_assert(I < DIM);
		this->v = v;
	}

	template<size_t I>
	T get() const {
		//static_assert(I < DIM);
		return v[I];
	}

public:
	std::array< T, DIM > v;
};

	}
}

#endif