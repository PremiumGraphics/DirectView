#include "gtest/gtest.h"
 
#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST( Vector3dTest, TestEquals )
{
	const Vector3d v1( 1.0f, 1.0f, 1.0f );
	const Vector3d v2( 2.0f, 1.0f, 1.0f );
	const Vector3d v3( 1.0f, 1.0f, 1.0f );

	EXPECT_EQ( v1, v3 );
	EXPECT_NE( v1, v2 );
}

TEST( Vector3dTest, TestScale )
{
	Vector3d v( 1.0f, 1.0f, 1.0f );
	const Vector3d& scaled = v.getScaled( 2.0f );
	EXPECT_EQ( scaled, Vector3d( 2.0f, 2.0f, 2.0f ) );
}
 
TEST( Vector3dTest, TestLength )
{
	Vector3d v( 1.0, 1.0, 1.0 );
	EXPECT_TRUE( Tolerances::isEqualLoosely( v.getLength(), std::sqrt( 3.0f ) ) );
	EXPECT_TRUE( Tolerances::isEqualStrictly( v.getLength(), std::sqrt( 3.0f ) ) );

	EXPECT_TRUE( Tolerances::isEqualStrictly( v.getLengthSquared(), 3.0f ) );
	EXPECT_TRUE( Tolerances::isEqualStrictly( v.getLengthSquared(), 3.0f ) );
}

TEST( Vector3dTest, TestInnerProduct )
{
	Vector3d v1( 2.0, 2.0, 2.0 );
	Vector3d v2( 1.0, 1.0, 2.0 );
	EXPECT_EQ( 8.0, v1.getInnerProduct( v2 ) );
}
 
TEST( Vector3dTest, TestDistance )
{
	Vector3d v0( 1.0f, 1.0f, 1.0f );
	Vector3d v1( 2.0f, 2.0f, 2.0f );
	EXPECT_TRUE( Tolerances::isEqualLoosely( v0.getDistance( v1 ), std::sqrt( 3.0f ) ) );
	EXPECT_TRUE( Tolerances::isEqualLoosely( v0.getDistance( v1 ), std::sqrt( 3.0f ) ) );
}

TEST( Vector3dTest, TestToArray )
{
	Vector3dVector vectors;
	vectors.push_back( Vector3d( 1.0f, 2.0f, 3.0f ) );
	vectors.push_back( Vector3d( 4.0f, 5.0f, 6.0f ) );
	const std::vector<float>& actual = toArray( vectors );
	std::vector<float> expected;
	expected.push_back( 1.0f );
	expected.push_back( 2.0f );
	expected.push_back( 3.0f );
	expected.push_back( 4.0f );
	expected.push_back( 5.0f );
	expected.push_back( 6.0f );

	EXPECT_EQ( expected, actual );
}