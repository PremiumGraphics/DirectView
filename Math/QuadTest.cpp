#include "gtest/gtest.h"
 
#include "../Math/Quad.h"

using namespace Crystal::Math;

TEST( QuadTest, TestConstruct )
{
	const Quad q;
	EXPECT_EQ( 1.0f, q.getLengthX() );
	EXPECT_EQ( 1.0f, q.getLengthY() );
	EXPECT_EQ(Vector2d<float>(0.0f, 0.0f), q.getCenter() );
}

TEST(QuadTest, TestConstructByLengths )
{
	const Quad q( 2.0f, 3.0f );
	EXPECT_EQ( 2.0f, q.getLengthX() );
	EXPECT_EQ( 3.0f, q.getLengthY() );
	EXPECT_EQ( Vector2d<float>(0.0f, 0.0f), q.getCenter() );
}

TEST(QuadTest, TestConstructByLengthsAndCenter)
{
	const Vector2d<float> center(5.0f, 6.0f);
	const Quad q(2.0f, 3.0f, center);
	EXPECT_EQ(2.0f, q.getLengthX());
	EXPECT_EQ(3.0f, q.getLengthY());
	EXPECT_EQ(center, q.getCenter());
}

TEST(QuadTest, TestConstructByTwoVector2ds)
{
	const Vector2d<float> v1(0.0f, 0.0f);
	const Vector2d<float> v2(2.0f, 3.0f);
	const Quad q( v1, v2 );
	EXPECT_EQ(2.0f, q.getLengthX());
	EXPECT_EQ(3.0f, q.getLengthY());
	EXPECT_EQ(Vector2d<float>(1.0f, 1.5f), q.getCenter() );
}

TEST(QuadTest, TestGetArea)
{
	const Vector2d<float> v1(0.0f, 0.0f);
	const Vector2d<float> v2(2.0f, 5.0f);
	const Quad q( v1, v2 );
	EXPECT_FLOAT_EQ(10.0f, q.getArea());
}