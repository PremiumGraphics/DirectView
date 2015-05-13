#ifndef __CRYSTAL_MATH_TOLERANCES_H__
#define __CRYSTAL_MATH_TOLERANCES_H__

#include <cmath>

#include "Tolerance.h"

namespace Crystal{
	namespace Math{

using Tolerances = Tolerance < float > ;
		/*
class Tolerances
{
public:

	static double getLooseTolerance() { return 1.0e-9; }

	static double getStrictTolerance() { return 1.0e-18; }

	static bool isEqualLoosely(double x) { return ::fabs( x ) < getLooseTolerance(); }

	static bool isEqualLoosely(double x, double y) { return ::fabs( x - y ) < getLooseTolerance(); }

	static bool isEqualStrictly(double x) { return ::fabs( x ) < getStrictTolerance(); }

	static bool isEqualStrictly(double x, double y) { 	return ::fabs( x - y ) < getStrictTolerance(); }

	static float getPI() { return 3.14159265359f; }

	static float getTwoPI() { return 2.0f * getPI(); }

	static double getPrecisePI() { return 3.141592653589793238462643383279; }
};
*/
/*
template<typename T>
class Tolerance
{

};

template<>
class Tolerance<float>
{

};
*/

	}
}

#endif