#include "gtest/gtest.h"
 
#include "../Math/Quad.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

template<class T>
class QuadTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(QuadTest, TestTypes);


TYPED_TEST( QuadTest, TestConstruct )
{
	using T = TypeParam;
	const Quad<T> q;
	EXPECT_EQ( 1.0f, q.getLengthX() );
	EXPECT_EQ( 1.0f, q.getLengthY() );
	EXPECT_EQ( Position2d<T>(0.0f, 0.0f), q.getCenter() );
}

TYPED_TEST(QuadTest, TestConstructByLengths )
{
	using T = TypeParam;
	const Quad<T> q(Vector2d <T>( 2.0f, 3.0f) );
	EXPECT_EQ( 2.0f, q.getLengthX() );
	EXPECT_EQ( 3.0f, q.getLengthY() );
	EXPECT_EQ( Position2d<T>(0.0f, 0.0f), q.getCenter() );
}

TYPED_TEST(QuadTest, TestConstructByLengthsAndCenter)
{
	using T = TypeParam;
	const Position2d<T> center(5.0f, 6.0f);
	const Quad<T> q( Vector2d<T>( 2.0f, 3.0f ), center);
	EXPECT_EQ(2.0f, q.getLengthX());
	EXPECT_EQ(3.0f, q.getLengthY());
	EXPECT_EQ(center, q.getCenter());
}

TYPED_TEST(QuadTest, TestConstructByTwoVector2ds)
{
	using T = TypeParam;
	const Position2d<T> v1(0.0f, 0.0f);
	const Position2d<T> v2(2.0f, 3.0f);
	const Quad<T> q( v1, v2 );
	EXPECT_EQ(2.0f, q.getLengthX());
	EXPECT_EQ(3.0f, q.getLengthY());
	EXPECT_EQ( Position2d<T>(1.0f, 1.5f), q.getCenter() );
}

TYPED_TEST(QuadTest, TestGetArea)
{
	using T = TypeParam;
	const Position2d<T> v1(0.0f, 0.0f);
	const Position2d<T> v2(2.0f, 5.0f);
	const Quad<T> q( v1, v2 );
	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(10.0, q.getArea()) );
}

/*
TEST(QuadTest, TestEquals)
{
	{
		const Position2d<float> v1(0.0f, 0.0f);
		const Position2d<float> v2(2.0f, 5.0f);
		const Quad q1(v1, v2);
		const Quad q2( Position2d<float>( 2.0f, 5.0f ), Vector2d<float>(1.0f, 2.5f));

		EXPECT_TRUE(q1.equals(q2));
		EXPECT_EQ(q1, q2);
	}

	{
		const Position2d<float> v1(0.0f, 0.0f);
		const Position2d<float> v2(2.0f, 5.0f);
		const Quad q1(v1, v2);
		const Quad q2( Vector2d<float>( 2.0f, 4.0f ), Vector2d<float>(1.0f, 2.5f));

		EXPECT_FALSE(q1.equals(q2));
		EXPECT_NE(q1, q2);
	}
}
*/

TYPED_TEST(QuadTest, TestHasIntersection)
{
	using T = TypeParam;

	const Position2d<T> v1(0.0f, 0.0f);
	const Position2d<T> v2(2.0f, 5.0f);

	const Quad<T> q1(v1, v2);
	const Quad<T> q2(v1, v2);
	EXPECT_TRUE(q1.hasIntersection(q2));
}