#ifndef __CRYSTAL_MATH_BOX_H__
#define __CRYSTAL_MATH_BOX_H__

#include "Primitive.h"

#include <vector>
#include <string>

namespace Crystal{
	namespace Math{

class Vector3d;
class Quad;

class Box : public Primitive
{
public:
	
	Box();

	Box(const Vector3d& pointX, const Vector3d& pointY);

	static Box Unit();

	virtual Type getType() const { return Primitive::Box; }

	virtual Vector3d getCenter() const;

	virtual Box getBoundingBox() const { return *this; }

	void add(const Vector3d& v);

	void add(const Box& b);
	
	float Box::getVolume() const;
	
	Vector3d Box::getMax() const;
	
	Vector3d Box::getMin() const;

	bool isInterior(const Vector3d &point) const;
	
	bool isExterior(const Vector3d &point) const;
	
	void outerOffset(const float offsetLength);
	
	Box getOuterOffset(const float offsetLength) const;

	void innerOffset(const float offsetLength);

	Box getInnerOffset(const float offsetLength) const;

	Vector3dVector toPoints( const float divideLength ) const;

	float getMaxX() const { return maxX; }

	float getMinX() const { return minX; }

	float getMaxY() const { return maxY; }

	float getMinY() const { return minY; }

	float getMaxZ() const { return maxZ; }

	float getMinZ() const { return minZ; }

	Vector3d getLength() const;

	virtual bool isValid() const;

	virtual bool isShirinked() const;

	bool equals(const Box& rhs) const;

	bool operator==( const Box& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box& rhs ) const { return !equals( rhs ); }

private:
	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;
};

	}
}

#endif