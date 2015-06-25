#ifndef __CRYSTAL_MATH_RANGE_H__
#define __CRYSTAL_MATH_RANGE_H__

namespace Crystal {
	namespace Math{

template<typename T>
class Range final
{
public:
	Range() :
		min_(0),
		max_(1)
	{}

	Range(const T min_, const T_max) :
		min_(min_),
		max_(max_)
	{}

	T getClamped(const T v) {
		return std::min<T>(getMax(), std::max<T>(getMin(), v));
	}

	/*
	T getNormalized() {

	}
	*/

private:
	T min_;
	T max_;


};
	}
}

#endif