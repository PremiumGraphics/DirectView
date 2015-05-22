#include "gtest/gtest.h"
 
#include "../Math/Vector3d.h"

using namespace Crystal::Math;

template<class T>
class Vector3dTest : public testing::Test {
};

typedef ::testing::Types<float> TestTypes;

TYPED_TEST_CASE(Vector3dTest, TestTypes);


TYPED_TEST(Vector3dTest, TestGet)
{
	using T = TypeParam;
	EXPECT_EQ(0, Vector3d_<T>().getX());
	EXPECT_EQ(0, Vector3d_<T>().getY());
	EXPECT_EQ(0, Vector3d_<T>().getZ());

	EXPECT_EQ(1, Vector3d_<T>(1, 2, 3).getX() );
	EXPECT_EQ(2, Vector3d_<T>(1, 2, 3).getY() );
	EXPECT_EQ(3, Vector3d_<T>(1, 2, 3).getZ() );
}

TYPED_TEST( Vector3dTest, TestEquals )
{
	using T = TypeParam;

	EXPECT_TRUE( Vector3d_<T>::Zero().equals( Vector3d_<T>::Zero() ) );
	EXPECT_EQ( Vector3d_<T>::Zero(), Vector3d_<T>::Zero());

	EXPECT_FALSE( Vector3d_<T>::Zero().equals( Vector3d_<T>::UnitX() ) );
	EXPECT_NE( Vector3d_<T>::Zero(), Vector3d_<T>::UnitX());
}

TYPED_TEST( Vector3dTest, TestScale )
{
	EXPECT_EQ(Vector3d(2.0f, 2.0f, 2.0f), Vector3d(1.0f, 1.0f, 1.0f).scale(2.0f));
	EXPECT_EQ(Vector3d(1.0f, 2.0f, 3.0f), Vector3d(0.5f, 1.0f, 1.5f).scale(2.0f));
}

TYPED_TEST(Vector3dTest, TestGetLengthSquared)
{
	const Vector3d v(1.0, 1.0, 1.0);
	const auto actual = v.getLengthSquared();
	const auto expected = 3.0f;
	EXPECT_FLOAT_EQ( expected, actual);
	EXPECT_TRUE( Tolerancef::isEqualLoosely(expected, actual) );
	EXPECT_TRUE( Tolerancef::isEqualStrictly(expected, actual) );
}

TYPED_TEST( Vector3dTest, TestGetLength )
{
	const Vector3d v( 1.0, 1.0, 1.0 );
	const auto actual = v.getLength();
	const auto expected = std::sqrt(3.0f);
	EXPECT_TRUE( Tolerancef::isEqualLoosely( expected, actual ) );
	EXPECT_TRUE( Tolerancef::isEqualStrictly( expected, actual ) );
}

TYPED_TEST( Vector3dTest, TestInnerProduct )
{
	const Vector3d v1( 2.0, 2.0, 2.0 );
	const Vector3d v2( 1.0, 1.0, 2.0 );
	EXPECT_EQ( 8.0, v1.getInnerProduct( v2 ) );
}
 
TYPED_TEST( Vector3dTest, TestGetDistance )
{
	const Vector3d v0( 1.0f, 1.0f, 1.0f );
	const Vector3d v1( 2.0f, 2.0f, 2.0f );
	EXPECT_TRUE( Tolerancef::isEqualLoosely( v0.getDistance( v1 ), std::sqrt( 3.0f ) ) );
	EXPECT_TRUE( Tolerancef::isEqualLoosely( v1.getDistance( v0 ), std::sqrt( 3.0f ) ) );
}

TYPED_TEST( Vector3dTest, TestToArray )
{
	const Vector3dVector vectors = {
		Vector3d(1.0f, 2.0f, 3.0f),
		Vector3d(4.0f, 5.0f, 6.0f)
	};
	const auto& actual = Vector3d::toArray( vectors );
	const std::vector<float> expected{ 1.0f, 2.0, 3.0f, 4.0, 5.0f, 6.0f };

	EXPECT_EQ( expected, actual );
}

TYPED_TEST(Vector3dTest, TestGetNormalized)
{
	EXPECT_EQ(Vector3d_<float>::UnitXYZ(), Vector3d_<float>(1.0f, 1.0f, 1.0f).getNormalized());
}

TYPED_TEST(Vector3dTest, TestRotateX)
{
	const Matrix3d<double> m = Matrix3d<double>::RotateX(180.0 * Tolerance<double>::getPI() / 180.0);
	Vector3d_<double> v = Vector3d_<double>(0.0f, 0.0, 1.0);
	v.rotate(m);
	Vector3d_<double> expected(0.0f, 0.0, -1.0);
	EXPECT_EQ(expected, v);
}

TYPED_TEST(Vector3dTest, TestRotateY)
{
	const Matrix3d<double> m = Matrix3d<double>::RotateY(180.0 * Tolerance<double>::getPI() / 180.0);
	Vector3d_<double> v = Vector3d_<double>(1.0f, 0.0, 0.0);
	v.rotate(m);
	Vector3d_<double> expected(-1.0f, 0.0, 0.0);
	EXPECT_EQ(expected, v);
}


TYPED_TEST(Vector3dTest, TestRotateZ)
{
	const Matrix3d<double> m = Matrix3d<double>::RotateZ(180.0 * Tolerance<double>::getPI() / 180.0);
	Vector3dd v = Vector3dd(1.0f, 0.0, 0.0);
	v.rotate(m);
	Vector3dd expected(-1.0f, 0.0, 0.0);
	EXPECT_EQ(expected, v);
};