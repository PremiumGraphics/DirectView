#include "gtest/gtest.h"

#include "../Math/Position1d.h"

using namespace Crystal::Math;

TEST(Position1dTest, TestGetDistanceSquared)
{
	EXPECT_EQ(0.0f, Position1d<float>().getDistance(Position1d<float>()));
}