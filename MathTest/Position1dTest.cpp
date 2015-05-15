#include "gtest/gtest.h"

#include "../Math/Position1d.h"

using namespace Crystal::Math;

TEST(Position1dTest, TestGetDistance)
{
	EXPECT_EQ(0.0f, Position1d<float>().getDistance(Position1d<float>()));
	EXPECT_EQ(1.0f, Position1d<float>(0.0f).getDistance(Position1d<float>(1.0f)));
}

TEST(Position1dTest, TestEquals)
{
	EXPECT_TRUE( Position1d<float>(0.0f).equals( Position1d<float>(0.0f) ) );
	EXPECT_EQ( Position1d<float>(0.0f), Position1d<float>(0.0f) );

	EXPECT_FALSE( Position1d<float>(0.0f).equals(Position1d<float>(1.0f) ) );
	EXPECT_NE( Position1d<float>(0.0f), Position1d<float>(1.0f) );
}

TEST(Position1dTest, TestMove)
{
	EXPECT_EQ( Position1d<float>(3.0f), Position1d<float>(1.0f).move(2.0f));
}