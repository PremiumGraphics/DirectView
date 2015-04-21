#ifndef __CRYSTAL_MATH_SPHERE_H__
#define __CRYSTAL_MATH_SPHERE_H__

#include "Primitive.h"

#include "Vector3d.h"

#include "Box.h"

#include <vector>
#include <cassert>
#include <algorithm>

namespace Crystal {
	namespace Math {
		class Box;

class Sphere : public Primitive
{
public:
	Sphere() :
		center( Vector3d::Zero() ),
		radius( 1.0f )
	{}

	Sphere( const Vector3d& center, const float radius ) :
		center( center ),
		radius( radius )
	{}

	Sphere( const Math::Box& boundingBox ) {
		center = boundingBox.getCenter();
		const Vector3d& length = boundingBox.getLength();
		radius = std::min<float>( std::min<float>( length.getX(), length.getY() ), length.getZ() ) * 0.5f;
	}

	static Sphere UnitSphere() {
		return Sphere( Vector3d::Zero(), 1.0f );
	}

	virtual Math::Box getBoundingBox() const {
		Math::Box box( center, center );
		return box.getOuterOffset( radius );
	}

	virtual Type getType() const { return Primitive::Sphere; }

	virtual Vector3dVector toPoints(const float divideLength ) const {
		Vector3dVector points;

		Math::Box box( center, center );
		box.outerOffset( radius );

		for( float x = box.getMinX(); x <= box.getMaxX(); x+= divideLength ) {
			for( float y = box.getMinY(); y <= box.getMaxY(); y += divideLength ) {
				for( float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength ) {
					const Vector3d pos( x, y, z );
					if( pos.getDistanceSquared( center ) < radius * radius ) {
						points.push_back( pos );
					}
				}
			}
		}
		return points;
	}


	virtual Vector3d getCenter() const { return center; }

	float getRadius() const { return radius; }

	virtual bool isValid() const {
		return radius >= 0.0f;
	}

	void outerOffset(const float offsetLength) {
		this->radius += offsetLength;
		assert( isValid() );
	}

	Sphere getOuterOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.radius += offsetLength;
		assert( sphere.isValid() );
		return sphere;
	}

	virtual void innerOffset(const float offsetLength) {
		this->radius -= offsetLength;
		assert( isValid() );
	}

	Sphere getInnerOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.radius -= offsetLength;
		assert( sphere.isValid() );
		return sphere;
	}

	bool equals( const Sphere& rhs ) const {
		return
			Tolerances::isEqualLoosely( radius, rhs.radius) &&
			( center == rhs.center );
	}

	bool operator==( const Sphere& rhs ) const {
		return equals( rhs );
	}

	bool isOuter(const Vector3d& v) const {
		return v.getDistanceSquared(center) > (radius * radius);
	}

	bool isInner(const Vector3d& v) const {
		return !isOuter(v);
	}

	bool isOnStrictly(const Vector3d& v) const {
		return Tolerances::isEqualStrictly(v.getDistanceSquared(center), radius * radius);
	}

	bool isOnLoosely(const Vector3d& v) const {
		return Tolerances::isEqualLoosely(v.getDistanceSquared(center), radius * radius);
	}

private:
	Vector3d center;
	float radius;
};

	}
}

#endif