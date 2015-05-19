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

	Box_(const Position3d<T>& pointX, const Position3d<T>& pointY) :
		maxX(std::max<T>(pointX.getX(), pointY.getX())),
		maxY(std::max<T>(pointX.getY(), pointY.getY())),
		maxZ(std::max<T>(pointX.getZ(), pointY.getZ()))
	{
		const auto x = std::min<T>(pointX.getX(), pointY.getX());
		const auto y = std::min<T>(pointX.getY(), pointY.getY());
		const auto z = std::min<T>(pointX.getZ(), pointY.getZ());
		this->start = Position3d<T>(x, y, z);

		assert(isValid());
	}


	Box_(const Vector3d& pointX, const Vector3d& pointY) :
		maxX(std::max<T>(pointX.getX(), pointY.getX())),
		maxY(std::max<T>(pointX.getY(), pointY.getY())),
		maxZ(std::max<T>(pointX.getZ(), pointY.getZ()))
	{
		const auto x = std::min<T>(pointX.getX(), pointY.getX());
		const auto y = std::min<T>(pointX.getY(), pointY.getY());
		const auto z = std::min<T>(pointX.getZ(), pointY.getZ());
		this->start = Position3d<T>(x, y, z);

		assert(isValid());
	}


	static Box_ Unit() {
		return Box_();
	}

	Box_ getBoundingBox() const { return *this; }

	void add(const Vector3d& v) {
		const auto x = std::min<T>( getMinX(), v.getX());
		const auto y = std::min<T>( getMinY(), v.getY());
		const auto z = std::min<T>( getMinZ(), v.getZ());
		start = Position3d <T>(x, y, z);

		maxX = std::max<T>(maxX, v.getX());
		maxY = std::max<T>(maxY, v.getY());
		maxZ = std::max<T>(maxZ, v.getZ());
	}

	void add(const Box_& b) {
		const auto x = std::min<T>( getMinX(), b.getMinX());
		const auto y = std::min<T>( getMinY(), b.getMinY());
		const auto z = std::min<T>( getMinZ(), b.getMinZ());

		maxX = std::max<T>(maxX, b.getMaxX());
		maxY = std::max<T>(maxY, b.getMaxY());
		maxZ = std::max<T>(maxZ, b.getMaxZ());
	}
	
	T getVolume() const {
		return (maxX - getMinX()) * (maxY - getMinY()) * (maxZ - getMinZ());
	}
	
	Position3d<T> getMax() const {
		return Position3d<T>(maxX, maxY, maxZ);
	}
	
	Position3d<T> getMin() const {
		return Position3d<T>(getMinX(), getMinY(), getMinZ());
	}

	Position3d<T> getStart() const {
		return getMin();
	}

	Position3d<T> getEnd() const {
		return getMax();
	}

	Position3d<T> getCenter() const {
		return Position3d<T>(
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
	
	void outerOffset(const T offsetLength) {
		const auto x = getMinX() - offsetLength;
		const auto y = getMinY() - offsetLength;
		const auto z = getMinZ() - offsetLength;
		start = Position3d<T>(x, y, z);
		maxX += offsetLength;
		maxY += offsetLength;
		maxZ += offsetLength;
		assert(isValid());
	}
	
	Box_ getOuterOffset(const T offsetLength) const {
		Box_ box = *this;
		box.outerOffset(offsetLength);
		return box;
	}

	void innerOffset(const T offsetLength) {
		outerOffset(-offsetLength);
		assert(isValid());
	}

	Box_ getInnerOffset(const T offsetLength) const {
		return getOuterOffset(-offsetLength);
	}

	Vector3dVector toPoints(const T divideLength) const {
		Vector3dVector points;
		for (T x = getMinX(); x <= maxX; x += divideLength) {
			for (T y = getMinY(); y <= maxY; y += divideLength) {
				for (T z = getMinZ(); z <= maxZ; z += divideLength) {
					points.push_back(Vector3d(x, y, z));
				}
			}
		}
		return points;
	}

	T getMaxX() const { return maxX; }

	T getMinX() const { return start.getX(); }

	T getMaxY() const { return maxY; }

	T getMinY() const { return start.getY(); }

	T getMaxZ() const { return maxZ; }

	T getMinZ() const { return start.getZ(); }

	Vector3d_<T> getLength() const {
		return Vector3d_<T>(maxX - getMinX(), maxY - getMinY(), maxZ - getMinZ());
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
			Tolerance<T>::isEqualLoosely(maxX, rhs.maxX) &&
			Tolerance<T>::isEqualLoosely(maxY, rhs.maxY) &&
			Tolerance<T>::isEqualLoosely(maxZ, rhs.maxZ);
	}

	bool operator==( const Box_& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box_& rhs ) const { return !equals( rhs ); }

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
		const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
		const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());
		const auto minz = std::max<T>(this->getStart().getZ(), rhs.getStart().getZ());

		const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
		const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());
		const auto maxz = std::min<T>(this->getEnd().getZ(), rhs.getEnd().getZ());

		const Position3d<T> min_(minx, miny, minz);
		const Position3d<T> max_(maxx, maxy, maxz);
		return Box_(min_, max_);
	}


private:
	T maxX;
	//T minX;
	T maxY;
	//T minY;
	T maxZ;
//	T minZ;
	Position3d<T> start;
};

using Box = Box_ < float > ;

	}
}

#endif