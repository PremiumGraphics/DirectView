#ifndef __CRYSTAL_MATH_PARAMETER_H__
#define __CRYSTAL_MATH_PARAMETER_H__

#include "Range.h"

namespace Crystal {
	namespace Math {

class Parameter final
{
public:
	explicit Parameter(const float param) :
		param(param)
	{}

	float get() const { return param; }

private:
	float param;
};
	}
}

#endif