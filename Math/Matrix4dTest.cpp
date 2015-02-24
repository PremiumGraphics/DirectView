#include "gtest/gtest.h"
 
#include "Matrix4d.h"

using namespace Crystal::Math;



TEST( Matrix4dTest, ContructTest )
{
	Matrix4d<float> m;
	EXPECT_EQ( Matrix4d<float>::Identity(), m );
}

TEST( Matrix4dTest, RotateYTest )
{
	EXPECT_EQ( Matrix4d<float>::Identity(), Matrix4d<float>::RotateX( 0.0f ) );
	EXPECT_EQ( Matrix4d<float>::Identity(), Matrix4d<float>::RotateY( 0.0f ) );
	EXPECT_EQ( Matrix4d<float>::Identity(), Matrix4d<float>::RotateZ( 0.0f ) );
}

TEST( Matrix4dTest, toArraysTest )
{
	const Matrix4d<float>& m = Matrix4d<float>::Identity();
	std::vector< float > x = m.toArray4x4();
	EXPECT_EQ( x[0], 1.0f );
	EXPECT_EQ( x[1], 0.0f );
	EXPECT_EQ( x[2], 0.0f );
	EXPECT_EQ( x[3], 0.0f );
}

TEST( Matrix2dTest, TestEquals )
{
	const Matrix4d<float>& m1 = Matrix4d<float>::Zero();
	const Matrix4d<float>& m2 = Matrix4d<float>::Identity();
	EXPECT_NE( m1, m2 );
}