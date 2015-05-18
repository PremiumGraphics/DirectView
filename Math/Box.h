#ifndef __CRYSTAL_MATH_BOX_H__
#define __CRYSTAL_MATH_BOX_H__

#include "Vector3d.h"
#include "Position3d.h"

#include <vector>
#include <string>
#include <algorithm>

namespace Crystal{
	namespace Math{

class Box final
{
public:
	
	Box();

	Box(const Vector3d& pointX, const Vector3d& pointY);

	static Box Unit();

	Box getBoundingBox() const { return *this; }

	void add(const Vector3d& v);

	void add(const Box& b) {
		minX = std::min<float>(minX, b.getMinX());
		minY = std::min<float>(minY, b.getMinY());
		minZ = std::min<float>(minZ, b.getMinZ());

		maxX = std::max<float>(maxX, b.getMaxX());
		maxY = std::max<float>(maxY, b.getMaxY());
		maxZ = std::max<float>(maxZ, b.getMaxZ());
	}
	
	float getVolume() const;
	
	Position3d<float> getMax() const {
		return Position3d<float>(maxX, maxY, maxZ);
	}
	
	Position3d<float> getMin() const {
		return Position3d<float>(minX, minY, minZ);
	}

	Position3d<float> getCenter() const {
		return Position3d<float>(
			(minX + maxX) * 0.5f,
			(minY + maxY) * 0.5f,
			(minZ + maxZ) * 0.5f
			);
	}


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

	Vector3d getLength() const {
		return Vector3d(maxX - minX, maxY - minY, maxZ - minZ);
	}

	virtual bool isValid() const {
		return
			(minX <= maxX) && (minY <= maxY) && (minZ <= maxZ);
	}

	virtual bool isShirinked() const;

	bool equals(const Box& rhs) const {
		return
			Tolerancef::isEqualLoosely(minX, rhs.minX) &&
			Tolerancef::isEqualLoosely(minY, rhs.minY) &&
			Tolerancef::isEqualLoosely(minZ, rhs.minZ) &&
			Tolerancef::isEqualLoosely(maxX, rhs.maxX) &&
			Tolerancef::isEqualLoosely(maxY, rhs.maxY) &&
			Tolerancef::isEqualLoosely(maxZ, rhs.maxZ);
	}

	bool operator==( const Box& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box& rhs ) const { return !equals( rhs ); }

	bool hasIntersection(const Box& rhs) const {
		const auto distx = fabs(maxX - minX);
		if ( distx < getLength().getX() ) {
			return true;
		}
		const auto disty = fabs(maxY - minY);
		if  (disty < getLength().getY() ) {
			return true;
		}
		const auto distz = fabs(maxZ - minZ);
		if ( distz < getLength().getZ() ) {
			return true;
		}
		return false;
	}

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