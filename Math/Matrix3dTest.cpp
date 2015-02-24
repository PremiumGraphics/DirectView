#include "gtest/gtest.h"
 
#include "../Math/Matrix3d.h"

using namespace Crystal::Math;


template<class T>
class Matrix3dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Matrix3dTest, TestTypes);

 
TYPED_TEST( Matrix3dTest, TestConstruct )
{
	Matrix3d<TypeParam> m;
	EXPECT_TRUE( m.isIdentity() );
}

TYPED_TEST( Matrix3dTest, RotateXTest )
{
	EXPECT_EQ( Matrix3d<TypeParam>::Identity(), Matrix3d<TypeParam>::RotateX( 0.0f ) );

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

TYPED_TEST( Matrix3dTest, RotateYTest )
{
	EXPECT_EQ(Matrix3d<TypeParam>::Identity(), Matrix3d<TypeParam>::RotateY(0.0f));
}

TYPED_TEST( Matrix3dTest, RotateZTest )
{
	EXPECT_EQ(Matrix3d<TypeParam>::Identity(), Matrix3d<TypeParam>::RotateZ(0.0f));
}

TYPED_TEST( Matrix3dTest, ScaleTest )
{
	Matrix3d<TypeParam> m;
	m.setIdentity();

	const Matrix3d<TypeParam>& scaled = m.getScaled(2.0f);

	EXPECT_TRUE( m.isIdentity() );

	EXPECT_EQ(
		Matrix3d<TypeParam>(2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 2.0f),
		scaled );

	m.scale( 2.0f );

	EXPECT_EQ(
		Matrix3d<TypeParam>(2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 2.0f),
		m );

}