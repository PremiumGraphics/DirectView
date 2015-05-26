#include "gtest/gtest.h"

#include "../Math/Space.h"

using namespace Crystal::Math;

TEST(SpaceTest, TestGetStart)
{
	Space< float, 1 > space;
	EXPECT_EQ(Position1d<float>({ 0 }), space.getStart());
}