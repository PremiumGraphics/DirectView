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

TYPED_TEST( Matrix3dTest, TestRotateX )
{
	EXPECT_EQ(
		Matrix3d<TypeParam>::Identity(),
		Matrix3d<TypeParam>::RotateX(0.0f) );

	EXPECT_EQ(
		Matrix3d<double>( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f ),
		Matrix3d<double>::RotateX(90.0 / 180.0 * Tolerances::getPrecisePI()) );

	EXPECT_EQ(
		Matrix3d<double>( 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, -1.0 ),
		Matrix3d<double>::RotateX(180.0 / 180.0 * Tolerances::getPrecisePI()) );


	EXPECT_EQ(
		Matrix3d<double>( 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0 ),
		Matrix3d<double>::RotateX(270.0 / 180.0 * Tolerances::getPrecisePI() ) );

	EXPECT_EQ(
		Matrix3d<double>::Identity(),
		Matrix3d<double>::RotateX(360.0 / 180.0 * Tolerances::getPrecisePI() ) );
}

TYPED_TEST( Matrix3dTest, TestRotateY )
{
	EXPECT_EQ(
		Matrix3d<TypeParam>::Identity(),
		Matrix3d<TypeParam>::RotateY(0.0f) );

	EXPECT_EQ(
		Matrix3d<double>(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f),
		Matrix3d<double>::RotateY(90.0 / 180.0 * Tolerances::getPrecisePI()) );

	EXPECT_EQ(
		Matrix3d<double>(-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f),
		Matrix3d<double>::RotateY(180.0 / 180.0 * Tolerances::getPrecisePI()) );

	EXPECT_EQ(
		Matrix3d<double>( 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f ),
		Matrix3d<double>::RotateY(270.0 / 180.0 * Tolerances::getPrecisePI() ) );


	EXPECT_EQ(
		Matrix3d<double>::Identity(),
		Matrix3d<double>::RotateY(360.0 / 180.0 * Tolerances::getPrecisePI()));
}

TYPED_TEST( Matrix3dTest, TestRotateZ )
{
	EXPECT_EQ(Matrix3d<TypeParam>::Identity(), Matrix3d<TypeParam>::RotateZ(0.0f));

	{
		const Matrix3d<double> expected(
			0.0f, -1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateZ(90.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected(
			-1.0, 0.0, 0.0,
			0.0, -1.0, 0.0,
			0.0, 0.0, 1.0
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateZ(180.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected(
			0.0, 1.0, 0.0,
			-1.0, 0.0, 0.0,
			0.0, 0.0, 1.0
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateZ(270.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected = Matrix3d<double>::Identity();
		const Matrix3d<double>& actual = Matrix3d<double>::RotateZ(360.0 / 180.0 * Tolerances::getPrecisePI());
		EXPECT_EQ(expected, actual);
	}
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

TEST(Matrix3dTest, TestDeterminantFloat)
{
	EXPECT_FLOAT_EQ(0.0f, Matrix3d<float>::Zero().getDeterminant());
	EXPECT_FLOAT_EQ(1.0f, Matrix3d<float>::Identity().getDeterminant());
}

TEST(Matrix3dTest, TestDeterminantDouble)
{
	EXPECT_DOUBLE_EQ(0.0, Matrix3d<double>::Zero().getDeterminant());
	EXPECT_DOUBLE_EQ(1.0, Matrix3d<double>::Identity().getDeterminant());
}

TYPED_TEST(Matrix3dTest, TestInverse)
{
	const auto m = Matrix3d<TypeParam>::Identity();
	const auto i = m.getInverse();
	EXPECT_EQ( Matrix3d<TypeParam>::Identity(), i );
}