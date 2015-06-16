#include "gtest/gtest.h"

#include "../Math/Line.h"

using namespace Crystal::Math;

template<class T>
class LineTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(LineTest, TestTypes);


TYPED_TEST(LineTest, TestGetStart)
{
	using T = TypeParam;
	EXPECT_EQ(Position1d<T>({ 0.0 }), Line1d<T>().getStart());
	EXPECT_EQ(Position1d<T>({ 1.0 }), Line1d<T>(Position1d<T>({ 1.0 })).getStart());
	EXPECT_EQ(Position1d<T>({ 0.0 }), Line1d<T>(Position1d<T>({ 0.0 }), Position1d<T>({ 1.0 })).getStart());

	EXPECT_EQ(Position2d<T>({ 0.0f, 0.0f }), Line2d<T>().getStart());
	EXPECT_EQ(Position2d<T>({ 1.0f, 0.0f }), Line2d<T>(Position2d<T>({ 1.0f, 0.0f })).getStart());
	EXPECT_EQ(Vector3d_<T>({ 0.0f, 0.0f, 0.0f }), Line3d<T>().getStart());

}

/*
TYPED_TEST(Line1dTest, TestGetCenter)
{
	using T = TypeParam;
	EXPECT_EQ(Position1d<T>({ 0.5 }), Line1d<T>().getCenter());
	EXPECT_EQ(Position1d<T>({ 1.5 }), Line1d<T>(Position1d<T>({ 1.0 }), Position1d<T>({ 2.0f })).getCenter());
}
*/

TYPED_TEST(LineTest, TestGetEnd)
{
	using T = TypeParam;
	EXPECT_EQ(Position1d<T>({ 1 }), Line1d<T>(Position1d<T>({ 0 }), Vector1d<T>({ 1 })).getEnd());
	EXPECT_EQ(Position1d<T>({ 11 }), Line1d<T>(Position1d<T>({ 1 }), Vector1d<T>({ 10 })).getEnd());
	EXPECT_EQ(Position1d<T>({ 3 }), Line1d<T>(Position1d<T>({ 2 }), Position1d<T>({ 3 })).getEnd());
}

TYPED_TEST(LineTest, TestGetLength)
{
	using T = TypeParam;
	EXPECT_EQ(1, Line1d<T>(Position1d<T>({ 0 }), Vector1d<T>({ 1 })).getLength());
	EXPECT_EQ(10, Line1d<T>(Position1d<T>({ 1 }), Vector1d<T>({ 10 })).getLength());
	EXPECT_EQ(1, Line1d<T>(Position1d<T>({ 2 }), Position1d<T>({ 3 })).getLength());
	EXPECT_EQ(0, Line3d<T>().getLength());

}

/*
TYPED_TEST(Line1dTest, TestMove)
{
	using T = TypeParam;
	EXPECT_EQ( Line1d<T>(1.0f, 1.0f), Line1d<T>().move(1.0f) );
	EXPECT_EQ( Line1d<T>(11.0f, 1.0f), Line1d<T>( Position1d<T>(10.0f) ).move(1.0f) );
}

TYPED_TEST(Line1dTest, TestScale)
{
	using T = TypeParam;
	EXPECT_EQ(Line1d<T>(Position1d<T>({ 0 }), Vector1d<T>({ 10.0f }) ), Line1d<T>().scale(10.0f));
	EXPECT_EQ(Line1d<T>(Position1d<T>({ 5 }), Vector1d<T>({ 100.0f })), Line1d<T>(Position1d<T>({ 5 }), 10.0).scale(10.0f));

}

TYPED_TEST(Line1dTest, TestHasIntersection)
{
	using T = TypeParam;
	{
		const Line1d<T> line1(Position1d<T>({ 0.0 }), Position1d<T>({ 10 }));
		const Line1d<T> line2(Position1d<T>({ 5.0 }), Position1d<T>({ 10 }));
		EXPECT_TRUE(line1.hasIntersection(line2));
		EXPECT_TRUE(line2.hasIntersection(line1));
	}

	{
		const Line1d<T> line1(Position1d<T>({ 0.0 }), Position1d<T>({ 10 }));
		const Line1d<T> line2(Position1d<T>({ 20 }), Position1d<T>({ 40 }));
		EXPECT_FALSE(line1.hasIntersection(line2));
		EXPECT_FALSE(line2.hasIntersection(line1));

	}

	//EXPECT_TRUE( Line1d<T>(0.0f, 1.0f).hasIntersection(Line1d<T>(1.0f, 1.0f)));
}

TYPED_TEST(Line1dTest, TestGetOverlapped)
{
	using T = TypeParam;
	{
		const Line1d<T> line1(Position1d<T>({ 0.0 }), Position1d<T>({ 10 }));
		const Line1d<T> line2(Position1d<T>({ 5.0 }), Position1d<T>({ 10.0 }));
		const Line1d<T> actual = line1.getOverlapped(line2);
		const Line1d<T> expected(Position1d<T>({ 5.0 }), Position1d<T>({ 10.0 }));
		EXPECT_EQ(expected, actual);
	}
}
*/

