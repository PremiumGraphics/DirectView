#ifndef __CRYSTAL_MATH_PRIMITIVE_H__
#define __CRYSTAL_MATH_PRIMITIVE_H__

#include <vector>

#include "Vector3d.h"
#include <string>

namespace Crystal {
	namespace Math {
		class Box;

class Primitive
{
public:
	enum Type {
		Box,
		Sphere,
		Cylinder,
		Cone,
		Pyramid,
	};

	virtual Math::Box getBoundingBox() const = 0;

	virtual Type getType() const = 0;

	virtual Vector3dVector toPoints( const float divideLength ) const = 0;

	virtual Vector3d getCenter() const = 0;

	virtual bool isValid() const = 0;

	virtual void innerOffset(const float offsetLength) = 0;
};

typedef std::vector< Primitive* > PrimitiveVector;

	}
}


#endif