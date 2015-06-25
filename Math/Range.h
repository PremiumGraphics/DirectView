#ifndef __CRYSTAL_MATH_RANGE_H__
#define __CRYSTAL_MATH_RANGE_H__

#include <algorithm>

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

	Range(const T min_, const T max_) :
		min_(min_),
		max_(max_)
	{}

	T getClamped(const T v) {
		return std::min<T>(max_, std::max<T>(min_, v));
	}

	T getNormalized(const T v) {
		return (v - min_) / (max_ - min_);
	}

	bool isIn(const T v) {
		return min_ <= v && v <= max_;
	}

	bool isOut(const T v) {
		return !isIn(v);
	}

private:
	T min_;
	T max_;


};
	}
}

#endif