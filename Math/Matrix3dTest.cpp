#include "gtest/gtest.h"
 
#include "../Math/Matrix3d.h"

using namespace Crystal::Math;

 
TEST( Matrix3dTest, TestConstruct )
{
	Matrix3d m;
	EXPECT_TRUE( m.isIdentity() );
}

TEST( Matrix3dTest, RotateXTest )
{
	EXPECT_EQ( Matrix3d::Identity(), Matrix3d::RotateX( 0.0f ) );

	// TODOÅ@åÎç∑
	/*
	EXPECT_EQ(
		Matrix3d(
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f ),
		Matrix3d::RotateX( 90.0f / 180.0 * Tolerances::getPI() )
		); 
		*/
}

TEST( Matrix3dTest, RotateYTest )
{
	EXPECT_EQ( Matrix3d::Identity(), Matrix3d::RotateY( 0.0f ) );
}

TEST( Matrix3dTest, RotateZTest )
{
	EXPECT_EQ( Matrix3d::Identity(), Matrix3d::RotateZ( 0.0f ) );
}

TEST( Matrix3dTest, ScaleTest )
{
	Matrix3d m;
	m.setIdentity();

	const Matrix3d& scaled = m.getScaled( 2.0f );

	EXPECT_TRUE( m.isIdentity() );

	EXPECT_EQ(
		Matrix3d( 2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 2.0f),
		scaled );

	m.scale( 2.0f );

	EXPECT_EQ(
		Matrix3d( 2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 2.0f),
		m );

}