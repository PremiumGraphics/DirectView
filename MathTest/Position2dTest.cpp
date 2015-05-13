#include "gtest/gtest.h"

#include "../Math/Position2d.h"

using namespace Crystal::Math;

TEST(Position2dTest, TestGetDistanceSquared)
{
	EXPECT_EQ(0.0f, Position2d<float>().getDistanceSquared( Position2d<float>() ));
}