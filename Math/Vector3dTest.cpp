#include "gtest/gtest.h"
 
#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST(Vector3dTest, TestConstruct)
{
	const Vector3d v;
	EXPECT_EQ(0.0f, v.getX());
	EXPECT_EQ(0.0f, v.getY());
	EXPECT_EQ(0.0f, v.getZ());
}

TEST(Vector3dTest, TestConstrcutByXYZ)
{
	const Vector3d v(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(1.0f, v.getX());
	EXPECT_EQ(2.0f, v.getY());
	EXPECT_EQ(3.0f, v.getZ());
}

TEST( Vector3dTest, TestEquals )
{
	const Vector3d v1( 1.0f, 1.0f, 1.0f );
	const Vector3d v2( 2.0f, 1.0f, 1.0f );
	const Vector3d v3( 1.0f, 1.0f, 1.0f );

	EXPECT_TRUE(v1.equals(v3));
	EXPECT_FALSE(v1.equals(v2));

	EXPECT_EQ( v1, v3 );
	EXPECT_NE( v1, v2 );
}

TEST( Vector3dTest, TestScale )
{
	const Vector3d v( 1.0f, 1.0f, 1.0f );
	const Vector3d& scaled = v.getScaled( 2.0f );
	EXPECT_EQ( scaled, Vector3d( 2.0f, 2.0f, 2.0f ) );
}

TEST(Vector3dTest, TestGetLengthSquared)
{
	const Vector3d v(1.0, 1.0, 1.0);
	const auto actual = v.getLengthSquared();
	const auto expected = 3.0f;
	EXPECT_FLOAT_EQ( expected, actual);
	EXPECT_TRUE( Tolerances::isEqualLoosely(expected, actual) );
	EXPECT_TRUE( Tolerances::isEqualStrictly(expected, actual) );
}


TEST( Vector3dTest, TestGetLength )
{
	const Vector3d v( 1.0, 1.0, 1.0 );
	const auto actual = v.getLength();
	const auto expected = std::sqrt(3.0f);
	EXPECT_TRUE( Tolerances::isEqualLoosely( expected, actual ) );
	EXPECT_TRUE( Tolerances::isEqualStrictly( expected, actual ) );
}

TEST( Vector3dTest, TestInnerProduct )
{
	const Vector3d v1( 2.0, 2.0, 2.0 );
	const Vector3d v2( 1.0, 1.0, 2.0 );
	EXPECT_EQ( 8.0, v1.getInnerProduct( v2 ) );
}
 
TEST( Vector3dTest, TestGetDistance )
{
	const Vector3d v0( 1.0f, 1.0f, 1.0f );
	const Vector3d v1( 2.0f, 2.0f, 2.0f );
	EXPECT_TRUE( Tolerances::isEqualLoosely( v0.getDistance( v1 ), std::sqrt( 3.0f ) ) );
	EXPECT_TRUE( Tolerances::isEqualLoosely( v0.getDistance( v1 ), std::sqrt( 3.0f ) ) );
}

TEST( Vector3dTest, TestToArray )
{
	const Vector3dVector vectors = {
		Vector3d(1.0f, 2.0f, 3.0f),
		Vector3d(4.0f, 5.0f, 6.0f)
	};
	const auto& actual = toArray( vectors );
	const std::vector<float> expected{ 1.0f, 2.0, 3.0f, 4.0, 5.0f, 6.0f };

	EXPECT_EQ( expected, actual );
}

#include "Matrix3d.h"

TEST(Vector3dTest, TestRotateX)
{
	const Matrix3d<double> m = Matrix3d<double>::RotateX(180.0 * Tolerances::getPrecisePI() / 180.0);
	Vector3d v = Vector3d(0.0f, 0.0, 1.0);
	v.rotate(m);
	Vector3d expected(0.0f, 0.0, -1.0);
	EXPECT_EQ(expected, v);
}

TEST(Vector3dTest, TestRotateY)
{
	const Matrix3d<double> m = Matrix3d<double>::RotateY(180.0 * Tolerances::getPrecisePI() / 180.0);
	Vector3d v = Vector3d(1.0f, 0.0, 0.0);
	v.rotate(m);
	Vector3d expected(-1.0f, 0.0, 0.0);
	EXPECT_EQ(expected, v);
}


TEST(Vector3dTest, TestRotateZ)
{
	const Matrix3d<double> m = Matrix3d<double>::RotateZ(180.0 * Tolerances::getPrecisePI() / 180.0);
	Vector3d v = Vector3d(1.0f, 0.0, 0.0);
	v.rotate(m);
	Vector3d expected(-1.0f, 0.0, 0.0);
	EXPECT_EQ(expected, v);
};