#ifndef __CRSYTAL_MATH_VECTOR_2D_H__
#define __CRSYTAL_MATH_VECTOR_2D_H__


#include "Vector.h"

namespace Crystal{
	namespace Math{

template<typename T>
using Vector2d = Vector<T,2>;

template< typename T >
static Vector2d<T> operator*( float factor, const Vector2d<T>& rhs ) { return rhs.getScaled( factor ); }

template< typename T >
static Vector2d<T> operator/( float factor, const Vector2d<T>& rhs ) { return rhs.getScaled( 1.0f / factor ); }

	}
}



#endif