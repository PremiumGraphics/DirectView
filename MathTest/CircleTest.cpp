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

TEST( CircleTest, TestToPoints )
{
	Circle c;
	const Vector3dVector& points = c.toPoints( 120.0f );
	EXPECT_EQ( 3, points.size() );
}

TEST( CircleTest, TestOffset )
{
	Circle c( 5.0f );
	c.innerOffset( 1.0f );
	EXPECT_EQ( 4.0f, c.getRadius() );

	c.outerOffset( 2.0f );
	EXPECT_EQ( 6.0f, c.getRadius() );
}

TEST(CircleTest, TestArea)
{
	{
		Circle c;
		const float actual = c.getArea();
		EXPECT_FLOAT_EQ(Tolerancef::getPI(), actual);
	}

	{
		Circle c(2.0);
		const float actual = c.getArea();
		const float expected = Tolerancef::getPI() * 4.0f;
		EXPECT_FLOAT_EQ( expected, actual);
	}
}

TEST(CircleTest, TestDiameter)
{
	Circle c;
	EXPECT_FLOAT_EQ(2.0f, c.getDiameter());
}