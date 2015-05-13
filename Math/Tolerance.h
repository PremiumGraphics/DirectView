#ifndef __CRYSTAL_MATH_TOLERANCE_H__
#define __CRYSTAL_MATH_TOLERANCE_H__

namespace Crystal {
	namespace Math {

template<typename T>
class Tolerance
{
public:
	static T getLooseTolerance() {
		static_assert(false);
	}

	static T getStrictTolerance() {
		static_assert(false);
	}

};

template<>
class Tolerance < float >
{
public:
	static float getLooseTolerance() {
		return 1.0e-9f;
	}

	static float getStrictTolerance() {
		return 1.0e-18f;
	}
};

template<>
class Tolerance < double >
{
public:
	static double getLooseTolerance() {
		return 1.0e-9;
	}

	static double getStrictTolerance() {
		return 1.0e-18;
	}
};


	}
}

#endif