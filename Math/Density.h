#ifndef __CRYSTAL_MATH_DENSITY_H__
#define __CRSYTAL_MATH_DENSITY_H__

#include <algorithm>

namespace Crystal {
	namespace Math {

template<typename T>
class Density final
{
public:
	Density() :
		value(0)
	{}

	explicit Density(const T v) :
		value(v)
	{}

	void add(const T v) { this->value = clamp(value + v); }

	void sub(const T v) { this->value = clamp(value - v); }

	T get() const { return value; }

	//static getNormalized() { return  }

	static T getMin() { return -1; }
	
	static T getMax() { return 1; }

	Density& operator+=(const Density& rhs) {
		add(rhs.value);
		return (*this);
	}

	Density& operator-=(const Density& rhs) {
		sub(rhs.value);
		return (*this);
	}

private:
	T value;

	T clamp(const T v) {
		return std::min<T>( getMax(), std::max<T>(getMin(), v) );
	}
};
	}
}

#endif