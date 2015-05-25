#include "gtest/gtest.h"

#include "../Math/Position.h"

using namespace Crystal::Math;

template<class T>
class PositionTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(PositionTest, TestTypes);


TYPED_TEST(PositionTest, TestGetDistance)
{
	using T = TypeParam;
	EXPECT_EQ( 0, Position1d<T>().getDistance(Position1d<T>()));
	EXPECT_EQ( 1, Position1d<T>({ 0 }).getDistance(Position1d<T>({ 1 })));
}

TYPED_TEST(PositionTest, TestEquals)
{
	using T = TypeParam;

	EXPECT_TRUE(Position1d<T>({ 0 }).equals(Position1d<T>({ 0.0f })));
	EXPECT_EQ(Position1d<T>({ 0 }), Position1d<T>({ 0.0f }));

	EXPECT_FALSE(Position1d<T>({ 0 }).equals(Position1d<T>({ 1.0f })));
	EXPECT_NE(Position1d<T>({ 0 }), Position1d<T>({ 1.0f }));
}

/*
TEST(Position1dTest, TestMove)
{
	EXPECT_EQ(Position1d<float>({ 3 }), Position1d<float>({ 1 }).move(2.0f));
}
*/

TYPED_TEST(PositionTest, TestGet)
{
	using T = TypeParam;

	EXPECT_EQ( 0, Position2d<T>().get(0));
	EXPECT_EQ( 1, Position2d<T>({ 1, 2 }).get(0));
	EXPECT_EQ( 0, Position2d<T>().get(1));
	EXPECT_EQ( 2, Position2d<T>({ 1, 2 }).get(1));
}

TYPED_TEST(PositionTest, TestGetDistanceSquared)
{
	using T = TypeParam;
	EXPECT_EQ( 0, Position2d<T>().getDistanceSquared(Position2d<T>()));
}
