#ifndef __CRYSTAL_MATH_BoxH__
#define __CRYSTAL_MATH_BoxH__

#include "Vector.h"

#include <vector>
#include <string>
#include <algorithm>

namespace Crystal{
	namespace Math{

template<typename T>
class Box final
{
public:
	
	Box() : Box(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f))
	{
	}

	Box(const Vector3d<T>& pointX, const Vector3d<T>& pointY) :
		maxX(std::max<T>(pointX.getX(), pointY.getX())),
		maxY(std::max<T>(pointX.getY(), pointY.getY())),
		maxZ(std::max<T>(pointX.getZ(), pointY.getZ()))
	{
		const auto x = std::min<T>(pointX.getX(), pointY.getX());
		const auto y = std::min<T>(pointX.getY(), pointY.getY());
		const auto z = std::min<T>(pointX.getZ(), pointY.getZ());
		this->start = Vector3d<T>(x, y, z);

		assert(isValid());
	}

	static Box Unit() {
		return Box();
	}

	Box getBoundingBox() const { return *this; }

	void add(const Vector3d<T>& v) {
		const auto x = std::min<T>( getMinX(), v.getX());
		const auto y = std::min<T>( getMinY(), v.getY());
		const auto z = std::min<T>( getMinZ(), v.getZ());
		start = Vector3d <T>(x, y, z);

		maxX = std::max<T>(maxX, v.getX());
		maxY = std::max<T>(maxY, v.getY());
		maxZ = std::max<T>(maxZ, v.getZ());
	}

	void add(const Box& b) {
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
	
	Vector3d<T> getMax() const {
		return Vector3d<T>(maxX, maxY, maxZ);
	}
	
	Vector3d<T> getMin() const {
		return Vector3d<T>(getMinX(), getMinY(), getMinZ());
	}

	Vector3d<T> getStart() const {
		return getMin();
	}

	Vector3d<T> getEnd() const {
		return getMax();
	}

	Vector3d<T> getCenter() const {
		return Vector3d<T>(
			(getMinX() + maxX) * 0.5f,
			(getMinY() + maxY) * 0.5f,
			(getMinZ() + maxZ) * 0.5f
			);
	}


	bool isInterior(const Vector3d<T>& point) const {
		const bool xIsInterior = (getMinX() < point.getX() && point.getX() < maxX);
		const bool yIsInterior = (getMinY() < point.getY() && point.getY() < maxY);
		const bool zIsInterior = (getMinZ() < point.getZ() && point.getZ() < maxZ);
		return xIsInterior && yIsInterior && zIsInterior;
	}
	
	bool isExterior(const Vector3d<T>& point) const {
		return !isInterior(point);
	}
	
	void outerOffset(const T offsetLength) {
		const auto x = getMinX() - offsetLength;
		const auto y = getMinY() - offsetLength;
		const auto z = getMinZ() - offsetLength;
		start = Vector3d<T>(x, y, z);
		maxX += offsetLength;
		maxY += offsetLength;
		maxZ += offsetLength;
		assert(isValid());
	}
	
	Box getOuterOffset(const T offsetLength) const {
		Box box = *this;
		box.outerOffset(offsetLength);
		return box;
	}

	void innerOffset(const T offsetLength) {
		outerOffset(-offsetLength);
		assert(isValid());
	}

	Box getInnerOffset(const T offsetLength) const {
		return getOuterOffset(-offsetLength);
	}

	Vector3dVector<T> toPoints(const T divideLength) const {
		Vector3dVector<T> points;
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

	Vector3d<T> getLength() const {
		return Vector3d<T>(maxX - getMinX(), maxY - getMinY(), maxZ - getMinZ());
	}

	bool isValid() const {
		return
			(getMinX() <= maxX) && (getMinY() <= maxY) && (getMinZ() <= maxZ);
	}

	bool isShirinked() const{
		return
			(getMinX() == maxX) && (getMinY() == maxY) && (getMinZ() == maxZ);
	}

	bool equals(const Box& rhs) const {
		return
			start == rhs.getStart() &&
			Tolerance<T>::isEqualLoosely(maxX, rhs.maxX) &&
			Tolerance<T>::isEqualLoosely(maxY, rhs.maxY) &&
			Tolerance<T>::isEqualLoosely(maxZ, rhs.maxZ);
	}

	bool operator==( const Box& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box& rhs ) const { return !equals( rhs ); }

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
		const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
		const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());
		const auto minz = std::max<T>(this->getStart().getZ(), rhs.getStart().getZ());

		const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
		const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());
		const auto maxz = std::min<T>(this->getEnd().getZ(), rhs.getEnd().getZ());

		const Vector3d<T> min_(minx, miny, minz);
		const Vector3d<T> max_(maxx, maxy, maxz);
		return Box(min_, max_);
	}


private:
	T maxX;
	T maxY;
	T maxZ;
	Vector3d<T> start;
};

	}
}

#endif