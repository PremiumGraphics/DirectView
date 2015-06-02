#include "gtest/gtest.h"

#include "../Math/GridSpace.h"

using namespace Crystal::Math;

TEST(GridSpace3dTest, TestGetStart)
{
	using T = float;
	GridSpace3d<T> gs;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), gs.getStart());
}