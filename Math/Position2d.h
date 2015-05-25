#ifndef __CRSYTAL_MATH_POSITION_2D_H__
#define __CRSYTAL_MATH_POSITION_2D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

#include "Vector.h"

#include "Position.h"

namespace Crystal{
	namespace Math{



template<typename T>
using Position2d = Position < T, 2 > ;

template<typename T>
using Position2dVector = std::vector < Position2d<T> >;

	}
}



#endif