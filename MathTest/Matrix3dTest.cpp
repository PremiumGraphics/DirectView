#include "gtest/gtest.h"
 
#include "../Math/Matrix3d.h"

using namespace Crystal::Math;


template<class T>
class Matrix3dTest : public testing::Test {
};

typedef ::testing::Types<double> TestTypes;

TYPED_TEST_CASE(Matrix3dTest, TestTypes);

 
TYPED_TEST( Matrix3dTest, TestConstruct )
{
	Matrix3d<TypeParam> m;
	EXPECT_TRUE( m.isIdentity() );
}

TYPED_TEST( Matrix3dTest, TestRotateX )
{
	using T = TypeParam;

	EXPECT_EQ(
		Matrix3d<T>::Identity(),
		Matrix3d<T>::RotateX(0.0f) );

	EXPECT_EQ(
		Matrix3d<T>( 1.0, 0.0, 0.0, 0.0, 0.0f, -1.0, 0.0, 1.0, 0.0 ),
		Matrix3d<T>::RotateX(Tolerance<T>::getHalfPI()));

	EXPECT_EQ(
		Matrix3d<T>( 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, -1.0 ),
		Matrix3d<T>::RotateX( Tolerance<T>::getPI() ) );

	EXPECT_EQ(
		Matrix3d<T>( 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0 ),
		Matrix3d<T>::RotateX(270.0 / 180.0 * Tolerance<T>::getPI()));

	EXPECT_EQ(
		Matrix3d<T>::Identity(),
		Matrix3d<T>::RotateX( Tolerance<T>::getTwoPI()));
}

TYPED_TEST( Matrix3dTest, TestRotateY )
{
	using T = TypeParam;

	EXPECT_EQ(
		Matrix3d<T>::Identity(),
		Matrix3d<T>::RotateY(0.0f) );

	EXPECT_EQ(
		Matrix3d<T>(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f),
		Matrix3d<T>::RotateY( Tolerance<T>::getHalfPI()));

	EXPECT_EQ(
		Matrix3d<T>(-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f),
		Matrix3d<T>::RotateY( Tolerance<T>::getPI()));

	EXPECT_EQ(
		Matrix3d<T>( 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f ),
		Matrix3d<T>::RotateY(270.0 / 180.0 * Tolerance<T>::getPI()));

	EXPECT_EQ(
		Matrix3d<T>::Identity(),
		Matrix3d<T>::RotateY( Tolerance<T>::getTwoPI()));
}

TYPED_TEST( Matrix3dTest, TestRotateZ )
{
	using T = TypeParam;

	EXPECT_EQ(
		Matrix3d<T>::Identity(),
		Matrix3d<T>::RotateZ(0.0f) );

	EXPECT_EQ(
		Matrix3d<T>( 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f ),
		Matrix3d<T>::RotateZ( Tolerance<T>::getHalfPI() ) );

	EXPECT_EQ(
		Matrix3d<T>(-1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0),
		Matrix3d<T>::RotateZ( Tolerance<T>::getPI() ) );

	EXPECT_EQ(
		Matrix3d<T>( 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0 ),
		Matrix3d<T>::RotateZ( 270.0 / 180.0 * Tolerance<T>::getPI()));

	EXPECT_EQ(
		Matrix3d<T>::Identity(),
		Matrix3d<double>::RotateZ( Tolerance<double>::getTwoPI()) );
}

TYPED_TEST( Matrix3dTest, TestScale )
{
	Matrix3d<TypeParam> m = Matrix3d<TypeParam>::Identity();
	EXPECT_TRUE(m.isIdentity());

	const Matrix3d<TypeParam>& scaled = m.getScaled(2.0f);

	const Matrix3d<TypeParam> expected(
		2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 2.0f
		);
	EXPECT_EQ( expected, scaled );

	m.scale( 2.0f );

	EXPECT_EQ( expected, m );
}

TYPED_TEST(Matrix3dTest, TestDeterminantFloat)
{
	EXPECT_TRUE( Tolerance<TypeParam>::isEqualStrictly(0.0f, Matrix3d<TypeParam>::Zero().getDeterminant()) );
	EXPECT_TRUE( Tolerance<TypeParam>::isEqualStrictly(1.0, Matrix3d<TypeParam>::Identity().getDeterminant()));
}

TYPED_TEST(Matrix3dTest, TestInverse)
{
	const auto m = Matrix3d<TypeParam>::Identity();
	const auto i = m.getInverse();
	EXPECT_EQ( Matrix3d<TypeParam>::Identity(), i );
}