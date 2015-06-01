#include "gtest/gtest.h"

#include "../Math/Grid.h"

using namespace Crystal::Math;

TEST(Grid1dTest, TestGetSize)
{
	using T = float;
	EXPECT_EQ(2, Grid1d<T>(2, 0).getSize());
}

TEST(Grid1dTest, TestGet)
{
	using T = float;
	EXPECT_EQ(0, Grid1d<T>(2, 0).get(0));
}

TEST(Grid2dTest, TestGetSize)
{
	using T = float;
	EXPECT_EQ(2, Grid2d<T>(2, 1).getSizeX());

}