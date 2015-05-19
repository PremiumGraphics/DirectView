#ifndef __CRYSTAL_MATH_BOX_H__
#define __CRYSTAL_MATH_BOX_H__

#include "Vector3d.h"
#include "Position3d.h"

#include <vector>
#include <string>
#include <algorithm>

namespace Crystal{
	namespace Math{

template<typename T>
class Box_ final
{
public:
	
	Box_() : Box_(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f))
	{
	}

	Box_(const Position3d<float>& pointX, const Position3d<float>& pointY) :
		maxX(std::max<float>(pointX.getX(), pointY.getX())),
		maxY(std::max<float>(pointX.getY(), pointY.getY())),
		maxZ(std::max<float>(pointX.getZ(), pointY.getZ()))
	{
		const auto x = std::min<float>(pointX.getX(), pointY.getX());
		const auto y = std::min<float>(pointX.getY(), pointY.getY());
		const auto z = std::min<float>(pointX.getZ(), pointY.getZ());
		this->start = Position3d<float>(x, y, z);

		assert(isValid());
	}


	Box_(const Vector3d& pointX, const Vector3d& pointY) :
		maxX(std::max<float>(pointX.getX(), pointY.getX())),
		maxY(std::max<float>(pointX.getY(), pointY.getY())),
		maxZ(std::max<float>(pointX.getZ(), pointY.getZ()))
	{
		const auto x = std::min<float>(pointX.getX(), pointY.getX());
		const auto y = std::min<float>(pointX.getY(), pointY.getY());
		const auto z = std::min<float>(pointX.getZ(), pointY.getZ());
		this->start = Position3d<float>(x, y, z);

		assert(isValid());
	}


	static Box_ Unit() {
		return Box_();
	}

	Box_ getBoundingBox() const { return *this; }

	void add(const Vector3d& v) {
		const auto x = std::min<float>( getMinX(), v.getX());
		const auto y = std::min<float>( getMinY(), v.getY());
		const auto z = std::min<float>( getMinZ(), v.getZ());
		start = Position3d <float>(x, y, z);

		maxX = std::max<float>(maxX, v.getX());
		maxY = std::max<float>(maxY, v.getY());
		maxZ = std::max<float>(maxZ, v.getZ());
	}

	void add(const Box_& b) {
		const auto x = std::min<float>( getMinX(), b.getMinX());
		const auto y = std::min<float>( getMinY(), b.getMinY());
		const auto z = std::min<float>( getMinZ(), b.getMinZ());

		maxX = std::max<float>(maxX, b.getMaxX());
		maxY = std::max<float>(maxY, b.getMaxY());
		maxZ = std::max<float>(maxZ, b.getMaxZ());
	}
	
	float getVolume() const {
		return (maxX - getMinX()) * (maxY - getMinY()) * (maxZ - getMinZ());
	}
	
	Position3d<float> getMax() const {
		return Position3d<float>(maxX, maxY, maxZ);
	}
	
	Position3d<float> getMin() const {
		return Position3d<float>(getMinX(), getMinY(), getMinZ());
	}

	Position3d<float> getStart() const {
		return getMin();
	}

	Position3d<float> getEnd() const {
		return getMax();
	}

	Position3d<float> getCenter() const {
		return Position3d<float>(
			(getMinX() + maxX) * 0.5f,
			(getMinY() + maxY) * 0.5f,
			(getMinZ() + maxZ) * 0.5f
			);
	}


	bool isInterior(const Vector3d &point) const {
		const bool xIsInterior = (getMinX() < point.getX() && point.getX() < maxX);
		const bool yIsInterior = (getMinY() < point.getY() && point.getY() < maxY);
		const bool zIsInterior = (getMinZ() < point.getZ() && point.getZ() < maxZ);
		return xIsInterior && yIsInterior && zIsInterior;
	}
	
	bool isExterior(const Vector3d &point) const {
		return !isInterior(point);
	}
	
	void outerOffset(const float offsetLength) {
		const auto x = getMinX() - offsetLength;
		const auto y = getMinY() - offsetLength;
		const auto z = getMinZ() - offsetLength;
		start = Position3d<float>(x, y, z);
		maxX += offsetLength;
		maxY += offsetLength;
		maxZ += offsetLength;
		assert(isValid());
	}
	
	Box_ getOuterOffset(const float offsetLength) const {
		Box_ box = *this;
		box.outerOffset(offsetLength);
		return box;
	}

	void innerOffset(const float offsetLength) {
		outerOffset(-offsetLength);
		assert(isValid());
	}

	Box_ getInnerOffset(const float offsetLength) const {
		return getOuterOffset(-offsetLength);
	}

	Vector3dVector toPoints(const float divideLength) const {
		Vector3dVector points;
		for (float x = getMinX(); x <= maxX; x += divideLength) {
			for (float y = getMinY(); y <= maxY; y += divideLength) {
				for (float z = getMinZ(); z <= maxZ; z += divideLength) {
					points.push_back(Vector3d(x, y, z));
				}
			}
		}
		return points;
	}

	float getMaxX() const { return maxX; }

	float getMinX() const { return start.getX(); }

	float getMaxY() const { return maxY; }

	float getMinY() const { return start.getY(); }

	float getMaxZ() const { return maxZ; }

	float getMinZ() const { return start.getZ(); }

	Vector3d getLength() const {
		return Vector3d(maxX - getMinX(), maxY - getMinY(), maxZ - getMinZ());
	}

	bool isValid() const {
		return
			(getMinX() <= maxX) && (getMinY() <= maxY) && (getMinZ() <= maxZ);
	}

	bool isShirinked() const{
		return
			(getMinX() == maxX) && (getMinY() == maxY) && (getMinZ() == maxZ);
	}

	bool equals(const Box_& rhs) const {
		return
			start == rhs.getStart() &&
			Tolerancef::isEqualLoosely(maxX, rhs.maxX) &&
			Tolerancef::isEqualLoosely(maxY, rhs.maxY) &&
			Tolerancef::isEqualLoosely(maxZ, rhs.maxZ);
	}

	bool operator==( const Box_& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box_& rhs ) const { return !equals( rhs ); }

	/*
	bool hasIntersection(const Box_& rhs) const {
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
	bool hasIntersection(const Box_& rhs) const {
		const auto distx = std::fabs(getCenter().getX() - rhs.getCenter().getX());
		const auto lx = getLength().getX() * 0.5 + rhs.getLength().getX() * 0.5;

		const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
		const auto ly = getLength().getY() * 0.5 + rhs.getLength().getY() * 0.5;

		const auto distz = std::fabs(getCenter().getZ() - rhs.getCenter().getZ());
		const auto lz = getLength().getZ() * 0.5 + rhs.getLength().getZ() * 0.5;

		return (distx < lx && disty < ly && distz < lz);
	}


	Box_ getOverlapped(const Box_& rhs) const {
		assert(hasIntersection(rhs));
		const auto minx = std::max<float>(this->getStart().getX(), rhs.getStart().getX());
		const auto miny = std::max<float>(this->getStart().getY(), rhs.getStart().getY());
		const auto minz = std::max<float>(this->getStart().getZ(), rhs.getStart().getZ());

		const auto maxx = std::min<float>(this->getEnd().getX(), rhs.getEnd().getX());
		const auto maxy = std::min<float>(this->getEnd().getY(), rhs.getEnd().getY());
		const auto maxz = std::min<float>(this->getEnd().getZ(), rhs.getEnd().getZ());

		const Position3d<float> min_(minx, miny, minz);
		const Position3d<float> max_(maxx, maxy, maxz);
		return Box_(min_, max_);
	}


private:
	float maxX;
	//float minX;
	float maxY;
	//float minY;
	float maxZ;
//	float minZ;
	Position3d<float> start;
};

using Box = Box_ < float > ;

	}
}

#endif