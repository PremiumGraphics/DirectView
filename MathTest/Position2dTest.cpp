#include "gtest/gtest.h"

#include "../Math/Position2d.h"

using namespace Crystal::Math;

TEST(Position2dTest, TestGetX)
{
	EXPECT_EQ(0.0f, Position2d<float>().getX());
	EXPECT_EQ(1.0f, Position2d<float>(1.0f, 2.0f).getX());
}

TEST(Position2dTest, TestGetY)
{
	EXPECT_EQ(0.0f, Position2d<float>().getY());
	EXPECT_EQ(2.0f, Position2d<float>(1.0f, 2.0f).getY());
}

TEST(Position2dTest, TestGetDistanceSquared)
{
	EXPECT_EQ(0.0f, Position2d<float>().getDistanceSquared(Position2d<float>()));
}
