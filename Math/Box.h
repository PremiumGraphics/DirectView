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
	
	Box() : Box(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f))
	{
	}

	Box(const Position3d<float>& pointX, const Position3d<float>& pointY) :
		maxX(std::max<float>(pointX.getX(), pointY.getX())),
		minX(std::min<float>(pointX.getX(), pointY.getX())),
		maxY(std::max<float>(pointX.getY(), pointY.getY())),
		minY(std::min<float>(pointX.getY(), pointY.getY())),
		maxZ(std::max<float>(pointX.getZ(), pointY.getZ())),
		minZ(std::min<float>(pointX.getZ(), pointY.getZ()))
	{
		assert(isValid());
	}


	Box(const Vector3d& pointX, const Vector3d& pointY) :
		maxX(std::max<float>(pointX.getX(), pointY.getX())),
		minX(std::min<float>(pointX.getX(), pointY.getX())),
		maxY(std::max<float>(pointX.getY(), pointY.getY())),
		minY(std::min<float>(pointX.getY(), pointY.getY())),
		maxZ(std::max<float>(pointX.getZ(), pointY.getZ())),
		minZ(std::min<float>(pointX.getZ(), pointY.getZ()))
	{
		assert(isValid());
	}


	static Box Unit() {
		return Box();
	}

	Box getBoundingBox() const { return *this; }

	void add(const Vector3d& v) {
		minX = std::min<float>(minX, v.getX());
		minY = std::min<float>(minY, v.getY());
		minZ = std::min<float>(minZ, v.getZ());

		maxX = std::max<float>(maxX, v.getX());
		maxY = std::max<float>(maxY, v.getY());
		maxZ = std::max<float>(maxZ, v.getZ());
	}

	void add(const Box& b) {
		minX = std::min<float>(minX, b.getMinX());
		minY = std::min<float>(minY, b.getMinY());
		minZ = std::min<float>(minZ, b.getMinZ());

		maxX = std::max<float>(maxX, b.getMaxX());
		maxY = std::max<float>(maxY, b.getMaxY());
		maxZ = std::max<float>(maxZ, b.getMaxZ());
	}
	
	float getVolume() const {
		return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
	}
	
	Position3d<float> getMax() const {
		return Position3d<float>(maxX, maxY, maxZ);
	}
	
	Position3d<float> getMin() const {
		return Position3d<float>(minX, minY, minZ);
	}

	Position3d<float> getStart() const {
		return getMin();
	}

	Position3d<float> getEnd() const {
		return getMax();
	}

	Position3d<float> getCenter() const {
		return Position3d<float>(
			(minX + maxX) * 0.5f,
			(minY + maxY) * 0.5f,
			(minZ + maxZ) * 0.5f
			);
	}


	bool isInterior(const Vector3d &point) const {
		const bool xIsInterior = (minX < point.getX() && point.getX() < maxX);
		const bool yIsInterior = (minY < point.getY() && point.getY() < maxY);
		const bool zIsInterior = (minZ < point.getZ() && point.getZ() < maxZ);
		return xIsInterior && yIsInterior && zIsInterior;
	}
	
	bool isExterior(const Vector3d &point) const {
		return !isInterior(point);
	}
	
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

	bool isValid() const {
		return
			(minX <= maxX) && (minY <= maxY) && (minZ <= maxZ);
	}

	bool isShirinked() const{
		return
			(minX == maxX) && (minY == maxY) && (minZ == maxZ);
	}

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

	/*
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
	*/
	bool hasIntersection(const Box& rhs) const {
		const auto distx = std::fabs(getCenter().getX() - rhs.getCenter().getX());
		const auto lx = getLength().getX() * 0.5 + rhs.getLength().getX() * 0.5;

		const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
		const auto ly = getLength().getY() * 0.5 + rhs.getLength().getY() * 0.5;

		const auto distz = std::fabs(getCenter().getZ() - rhs.getCenter().getZ());
		const auto lz = getLength().getZ() * 0.5 + rhs.getLength().getZ() * 0.5;

		return (distx < lx && disty < ly && distz < lz);
	}


	Box getOverlapped(const Box& rhs) const {
		assert(hasIntersection(rhs));
		const auto minx = std::max<float>(this->getStart().getX(), rhs.getStart().getX());
		const auto miny = std::max<float>(this->getStart().getY(), rhs.getStart().getY());
		const auto minz = std::max<float>(this->getStart().getZ(), rhs.getStart().getZ());

		const auto maxx = std::min<float>(this->getEnd().getX(), rhs.getEnd().getX());
		const auto maxy = std::min<float>(this->getEnd().getY(), rhs.getEnd().getY());
		const auto maxz = std::min<float>(this->getEnd().getZ(), rhs.getEnd().getZ());

		const Position3d<float> min_(minx, miny, minz);
		const Position3d<float> max_(maxx, maxy, maxz);
		return Box(min_, max_);
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