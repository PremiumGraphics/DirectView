#include "gtest/gtest.h"
 
#include "../Math/Quad.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

template<class T>
class QuadTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(QuadTest, TestTypes);


TYPED_TEST( QuadTest, TestGetLengthX )
{
	using T = TypeParam;
	EXPECT_EQ( 1.0f, Quad<T>().getLengthX() );
	EXPECT_EQ( 2.0f, Quad<T>(Vector2d<T>(2.0f, 3.0f), Position2d<T>(5.0f, 6.0f)).getLengthX());
	EXPECT_EQ( 2.0f, Quad<T>( Vector2d<T>(2.0f, 3.0f) ).getLengthX() );
}

TYPED_TEST(QuadTest, TestGetLengthY )
{
	using T = TypeParam;
	EXPECT_EQ( 1.0f, Quad<T>().getLengthY() );
	EXPECT_EQ( 3.0f, Quad<T>( Vector2d<T>(2.0f, 3.0f), Position2d<T>(5.0f, 6.0f) ).getLengthY() );
	EXPECT_EQ( 3.0f, Quad<T>( Vector2d<T>(2.0f, 3.0f) ).getLengthY() );
}

TYPED_TEST(QuadTest, TestGetCenter)
{
	using T = TypeParam;
	EXPECT_EQ( Position2d<T>(5.0f, 6.0f), Quad<T>(Vector2d<T>(2.0f, 3.0f), Position2d<T>(5.0f, 6.0f) ).getCenter());
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
	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(10.0, Quad<T>( Position2d<T>(0.0f, 0.0f), Position2d<T>(2.0f, 5.0f ) ).getArea() ) );
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