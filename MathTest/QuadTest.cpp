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

TEST(QuadTest, TestEquals)
{
	{
		const Vector2d<float> v1(0.0f, 0.0f);
		const Vector2d<float> v2(2.0f, 5.0f);
		const Quad q1(v1, v2);
		const Quad q2(2.0f, 5.0f, Vector2d<float>(1.0f, 2.5f));

		EXPECT_TRUE(q1.equals(q2));
		EXPECT_EQ(q1, q2);
	}

	{
		const Vector2d<float> v1(0.0f, 0.0f);
		const Vector2d<float> v2(2.0f, 5.0f);
		const Quad q1(v1, v2);
		const Quad q2(2.0f, 4.0f, Vector2d<float>(1.0f, 2.5f));

		EXPECT_FALSE(q1.equals(q2));
		EXPECT_NE(q1, q2);
	}
}

TEST(QuadTest, TestHasIntersection)
{
	const Vector2d<float> v1(0.0f, 0.0f);
	const Vector2d<float> v2(2.0f, 5.0f);

	const Quad q1(v1, v2);
	const Quad q2(v1, v2);
	EXPECT_TRUE(q1.hasIntersection(q2));
}