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

TEST(Grid2dTest, TestGetSizeX)
{
	using T = float;
	EXPECT_EQ(1, Grid2d<T>(1, 1).getSizeX());
	EXPECT_EQ(1, Grid2d<T>(1, 2).getSizeX());
	EXPECT_EQ(2, Grid2d<T>(2, 1).getSizeX());
	EXPECT_EQ(2, Grid2d<T>(2, 2).getSizeX());
}

TEST(Grid2dTest, TestGetSizeY)
{
	using T = float;
	EXPECT_EQ(1, Grid2d<T>(1, 1).getSizeY());
	EXPECT_EQ(2, Grid2d<T>(1, 2).getSizeY());
	EXPECT_EQ(1, Grid2d<T>(2, 1).getSizeY());
	EXPECT_EQ(2, Grid2d<T>(2, 2).getSizeY());
}

TEST(Grid3dTest, TestGetSizeX)
{
	using T = float;
	EXPECT_EQ(1, Grid3d<T>(1, 1, 1).getSizeX());
	EXPECT_EQ(1, Grid3d<T>(1, 1, 2).getSizeX());
	EXPECT_EQ(1, Grid3d<T>(1, 2, 1).getSizeX());
	EXPECT_EQ(1, Grid3d<T>(1, 2, 2).getSizeX());

	EXPECT_EQ(2, Grid3d<T>(2, 1, 1).getSizeX());
	EXPECT_EQ(2, Grid3d<T>(2, 1, 2).getSizeX());

}