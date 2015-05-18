#include "gtest/gtest.h"
 
#include "../Math/Circle.h"

using namespace Crystal::Math;
 
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

TEST(CirlceTest, TestIsValid)
{
	EXPECT_TRUE(Circle().isValid());
}

TEST(CircleTest, TestIsShrinked)
{
	EXPECT_FALSE(Circle().isShrinked());
}

TEST(CircleTest, TestArea)
{
	EXPECT_FLOAT_EQ(Tolerancef::getPI(), Circle().getArea());
	EXPECT_FLOAT_EQ(Tolerancef::getPI() * 4.0f, Circle(2.0f).getArea() );
}

TEST(CircleTest, TestGetRadius)
{
	EXPECT_FLOAT_EQ(1.0f, Circle().getRadius());
	EXPECT_FLOAT_EQ(2.0f, Circle(2.0f).getRadius());
}

TEST(CircleTest, TestGetDiameter)
{
	EXPECT_FLOAT_EQ(2.0f, Circle().getDiameter());
	EXPECT_FLOAT_EQ(4.0f, Circle(2.0f).getDiameter());
}