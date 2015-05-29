#ifndef __CRYSTAL_GRAPHICS_CAMERA_H__
#define __CRYSTAL_GRAPHICS_CAMERA_H__

#include "../Math/Matrix3d.h"
#include "../Math/Vector.h"

#include <memory>

namespace Crystal {
	namespace Graphics {

template< typename T >
class Camera{
public:
	Camera() :
		near_( 0.01f ),
		far_( 10.0f ),
		left( -0.5f ),
		right( 0.5f ),
		bottom( 0.0f ),
		top( 1.0f )
	{}

	Camera( const T near__, const T far__, const T left, const T right, const T bottom, const T top ) :
		near_( near__ ),
		far_( far__),
		left( left ),
		right( right ),
		bottom( bottom ),
		top( top )
	{}

	Math::Matrix4d<T> getModelviewMatrix() const {
		Math::Matrix4d<T> matrix;
		matrix.translate( pos.getX(), pos.getY(), pos.getZ() );
		matrix *= Math::Matrix4d<T>::RotateX( angle.getX() );
		matrix *= Math::Matrix4d<T>::RotateY( angle.getY() );
		matrix *= Math::Matrix4d<T>::RotateZ( angle.getZ() );
		return matrix;
	}

	Math::Matrix4d<float> getPerspectiveMatrix() const {
		const float dx = right - left;
		const float dy = top - bottom;
		const float dz = far_ - near_;

		/*Math::Matrix4d matrix
		matrix.x[ 0] =  2.0f / dx;
		matrix.x[ 5] =  2.0f / dy;
		matrix.x[10] = -1.0f / dz;
		matrix.x[11] = -1.0f;
		matrix.x[12] = -(right + left) / dx;
		matrix.x[13] = -(bottom + top) / dy;
		matrix.x[14] = -near_ / dz;	
		*/

		return Math::Matrix4d<T>(
			2.0f / dx, 0.0, 0.0, 0.0,
			0.0, 2.0f / dy, 0.0, 0.0,
			0.0, 0.0, -1.0f/ dz, -1.0f,
			-(right + left) / dx, -(bottom + top) / dy, -near_ / dz, 0.0f
			);
	}

	T getNear() const { return near_; }

	T getFar() const { return far_; }

	void move( const Math::Vector3d<float>& move ) { this->pos += move; }

	void setPos( const Math::Vector3d<float>& p ) { this->pos = p; }

	Math::Vector3d<T> getPos() const { return pos; }

	Math::Matrix4d<T> getOrthogonalMatrix() const {
		const T left = -0.5f;
		const T right = 0.5f;
		const T bottom = 0.0f;
		const T top = 1.0f;

		const T dx = right - left;
		const T dy = top - bottom;
		const T dz = far_ - near_;

		Math::Matrix4d<T> matrix;
		matrix.setIdentityMatrix();
		matrix.x[0] =  2.0f / dx;
		matrix.x[5] =  2.0f / dy;
		matrix.x[10] = -2.0f / dz;
		matrix.x[12] = -(right + left) / dx;
		matrix.x[13] = -(top + bottom) / dy;
		matrix.x[14] = -(far_ + near_) / dz;

		return matrix;
	}

	T getLeft() const { return left; }

	T getRight() const { return right; }

	T getBottom() const { return bottom; }

	T getTop() const { return top; }

	Math::Vector3d<float> getAngle() const { return angle; }

	void addAngle(const Math::Vector3d<T>& a ) { this->angle += a; }

	void setAngle(const Math::Vector3d<T>& a) { this->angle = a; }

	void setNear( const T n ) { this->near_ = n; } 

	void setFar( const T f ) { this->far_ = f; }

private:
	T near_;
	T far_;
	Math::Vector3d<T> pos;

	const T left;
	const T	right;
	const T bottom;
	const T top;

	Math::Vector3d<T> angle;
};

template<typename T>
using CameraSPtr = std::shared_ptr < Camera<T> > ;

	}
}

#endif