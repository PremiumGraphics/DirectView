#include "gtest/gtest.h"
 
#include "../Math/Circle.h"

using namespace Crystal::Math;

 
TEST( CircleTest, TestConstruct )
{
	Circle c;
	EXPECT_EQ( 1.0f, c.getRadius() );
	EXPECT_TRUE( c.isValid() );
	EXPECT_FALSE( c.isShrinked() );
}

TEST( CircleTest, toPointsTest )
{
	Circle c;
	const Vector3dVector& points = c.toPoints( 60.0f );
	EXPECT_EQ( 7, points.size() );
}

TEST( CircleTest, offsetTest )
{
	Circle c( 5.0f );
	c.innerOffset( 1.0f );
	EXPECT_EQ( 4.0f, c.getRadius() );

	c.outerOffset( 2.0f );
	EXPECT_EQ( 6.0f, c.getRadius() );
}