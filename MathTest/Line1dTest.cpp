#include "gtest/gtest.h"

#include "../Math/Line1d.h"

using namespace Crystal::Math;

template<class T>
class Line1dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Line1dTest, TestTypes);


TYPED_TEST(Line1dTest, TestGetStart)
{
	using T = TypeParam;
	EXPECT_EQ( Position1d<T>( 0.0 ), Line1d<T>().getStart());
	EXPECT_EQ( Position1d<T>( 1.0 ), Line1d<T>(1.0f).getStart());
}

TYPED_TEST(Line1dTest, TestGetEnd)
{
	using T = TypeParam;
	EXPECT_EQ(Position1d<T>(1.0), Line1d<T>().getEnd());
	EXPECT_EQ(Position1d<T>(11.0), Line1d<T>(1.0f, 10.0f).getEnd());
}

TYPED_TEST(Line1dTest, TestGetLength)
{
	using T = TypeParam;
	EXPECT_EQ( 1.0, Line1d<T>().getLength());
	EXPECT_EQ( 10.0, Line1d<T>(1.0f, 10.0f).getLength());
}

TYPED_TEST(Line1dTest, TestMove)
{
	using T = TypeParam;
	EXPECT_EQ( Line1d<T>(1.0f, 1.0f), Line1d<T>().move(1.0f) );
	EXPECT_EQ( Line1d<T>(11.0f, 1.0f), Line1d<T>(10.0f).move(1.0f) );
}

TYPED_TEST(Line1dTest, TestHasIntersection)
{
	using T = TypeParam;
	{
		const Line1d<T> line1(Position1d<T>(0.0), Position1d<T>(10.0f));
		const Line1d<T> line2(Position1d<T>(5.0), Position1d<T>(10.0f));
		EXPECT_TRUE(line1.hasIntersection(line2));
		//EXPECT_TRUE(line2.hasIntersection(line1));
	}

	{
		const Line1d<T> line1(Position1d<T>(0.0), Position1d<T>(10.0f));
		const Line1d<T> line2(Position1d<T>(20.0), Position1d<T>(40.0f));
		EXPECT_FALSE(line1.hasIntersection(line2));
	}

	//EXPECT_TRUE( Line1d<T>(0.0f, 1.0f).hasIntersection(Line1d<T>(1.0f, 1.0f)));

}