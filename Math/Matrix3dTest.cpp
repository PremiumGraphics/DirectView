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
	EXPECT_EQ(Matrix3d<TypeParam>::Identity(), Matrix3d<TypeParam>::RotateX(0.0f));

	{
		const Matrix3d<double> expected(
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 1.0f, 0.0f
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateX(90.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected(
			1.0, 0.0, 0.0,
			0.0, -1.0, 0.0,
			0.0, 0.0, -1.0
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateX(180.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected(
			1.0, 0.0, 0.0,
			0.0, 0.0, 1.0,
			0.0, -1.0, 0.0
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateX(270.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected = Matrix3d<double>::Identity();
		const Matrix3d<double>& actual = Matrix3d<double>::RotateX(360.0 / 180.0 * Tolerances::getPrecisePI());
		EXPECT_EQ(expected, actual);
	}
}

TYPED_TEST( Matrix3dTest, RotateYTest )
{
	EXPECT_EQ(Matrix3d<TypeParam>::Identity(), Matrix3d<TypeParam>::RotateY(0.0f));

	{
		const Matrix3d<double> expected(
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateY(90.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected(
			-1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, -1.0f
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateY(180.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix3d<double> expected(
			0.0f, 0.0f, -1.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f
			);
		const Matrix3d<double>& actual = Matrix3d<double>::RotateY(270.0 / 180.0 * Tolerances::getPrecisePI());

		EXPECT_EQ(expected, actual);
	}


	{
		const Matrix3d<double> expected = Matrix3d<double>::Identity();
		const Matrix3d<double>& actual = Matrix3d<double>::RotateY(360.0 / 180.0 * Tolerances::getPrecisePI());
		EXPECT_EQ(expected, actual);
	}
}

TYPED_TEST( Matrix3dTest, RotateZTest )
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
		const Matrix3d<double> expected = Matrix3d<double>::Identity();
		const Matrix3d<double>& actual = Matrix3d<double>::RotateZ(360.0 / 180.0 * Tolerances::getPrecisePI());
		EXPECT_EQ(expected, actual);
	}
}

TYPED_TEST( Matrix3dTest, ScaleTest )
{
	Matrix3d<TypeParam> m;
	m.setIdentity();

	const Matrix3d<TypeParam>& scaled = m.getScaled(2.0f);

	EXPECT_TRUE( m.isIdentity() );

	const Matrix3d<TypeParam> expected(
		2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 2.0f
		);
	EXPECT_EQ( expected, scaled );

	m.scale( 2.0f );

	EXPECT_EQ( expected, m );
}