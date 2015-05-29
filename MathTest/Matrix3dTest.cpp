#include "gtest/gtest.h"
 
#include "../Math/Matrix3d.h"

using namespace Crystal::Math;

template<class T>
class Matrix2dTest : public testing::Test {
};

typedef ::testing::Types<double> TestTypes;

TYPED_TEST_CASE(Matrix2dTest, TestTypes);

TYPED_TEST(Matrix2dTest, TestConstruct)
{
	Matrix2d< TypeParam > m;
	EXPECT_EQ(Matrix2d<TypeParam>::Identity(), m);
}

TYPED_TEST(Matrix2dTest, RotateTest)
{
	EXPECT_EQ(Matrix2d<TypeParam>::Identity(), Matrix2d<TypeParam>::Rotate(0.0));
}

TYPED_TEST(Matrix2dTest, DeterminentTest)
{
	{
		const Matrix2d<TypeParam>& m = Matrix2d<TypeParam>::Identity();
		EXPECT_EQ(1.0, m.getDeterminant());
	}

	{
		const Matrix2d<TypeParam>& m = Matrix2d<TypeParam>::Zero();
		EXPECT_EQ(0.0, m.getDeterminant());
	}
}

TYPED_TEST(Matrix2dTest, InverseTest)
{
	{
		Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
		EXPECT_TRUE(m.hasInverse());
		const Matrix2d<TypeParam>& i = m.getInverse();
		EXPECT_EQ(Matrix2d<TypeParam>::Identity(), i);
	}

	{
		Matrix2d<TypeParam> m
			(
			2, 5,
			1, 3
			);
		const Matrix2d<TypeParam>& actual = m.getInverse();
		const Matrix2d<TypeParam> expected
			(
			3, -5,
			-1, 2
			);
		EXPECT_EQ(expected, actual);
	}
}


TYPED_TEST(Matrix2dTest, TestProduct)
{
	{
		const Matrix2d<TypeParam>& m0 = Matrix2d<TypeParam>::Identity();
		const Matrix2d<TypeParam>& m1 = Matrix2d<TypeParam>::Identity();
		const Matrix2d<TypeParam>& actual = m0 * m1;
		const Matrix2d<TypeParam>& expected = Matrix2d<TypeParam>::Identity();
		EXPECT_EQ(expected, actual);
	}

	{
		const Matrix2d<TypeParam>& m0 = Matrix2d<TypeParam>::Identity();
		const Matrix2d<TypeParam>& m1 = Matrix2d<TypeParam>::Zero();
		const Matrix2d<TypeParam>& actual = m0 * m1;
		const Matrix2d<TypeParam>& expected = Matrix2d<TypeParam>::Zero();
		EXPECT_EQ(expected, actual);
	}


}

TYPED_TEST(Matrix2dTest, TestScale)
{
	{
		const Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
		const Matrix2d<TypeParam> actual = m.getScaled(2.0);
		const Matrix2d<TypeParam> expected
			(
			2.0, 0.0,
			0.0, 2.0
			);
		EXPECT_EQ(expected, actual);
	}

	{
		Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
		m.scale(2.0f);
		const Matrix2d<TypeParam> expected
			(
			2.0, 0.0,
			0.0, 2.0
			);
		EXPECT_EQ(expected, m);
	}
}

TYPED_TEST(Matrix2dTest, TestToArray)
{
	Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
	const std::vector<TypeParam>& values = m.toArray2x2();
	EXPECT_EQ(4, values.size());
	EXPECT_EQ(1, values[0]);
	EXPECT_EQ(0, values[1]);
	EXPECT_EQ(0, values[2]);
	EXPECT_EQ(1, values[3]);
}

template<class T>
class Matrix3dTest : public testing::Test {
};

//typedef ::testing::Types<double> TestTypes;

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
	using T = TypeParam;
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(0, Matrix3d<T>::Zero().getDeterminant()) );
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(1, Matrix3d<T>::Identity().getDeterminant()));
}

TYPED_TEST(Matrix3dTest, TestInverse)
{
	const auto m = Matrix3d<TypeParam>::Identity();
	const auto i = m.getInverse();
	EXPECT_EQ( Matrix3d<TypeParam>::Identity(), i );
}