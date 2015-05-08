#include "gtest/gtest.h"

#include "../Math/Grid3d.h"

using namespace Crystal::Math;

TEST(Grid3dTest, TestConstruct)
{
	const Grid3d<1, 2, 4, float > grid( 0.0f );
	EXPECT_EQ(1, grid.sizex());
	EXPECT_EQ(2, grid.sizey());
	EXPECT_EQ(4, grid.sizez());
	EXPECT_EQ(8, grid.size());
	EXPECT_EQ(0.0f, grid[0][0][0]);
	EXPECT_EQ(0.0f, grid[1][0][0]);
	EXPECT_EQ(0.0f, grid[2][0][0]);
	EXPECT_EQ(0.0f, grid[3][0][0]);
	EXPECT_EQ(0.0f, grid[0][1][0]);
	EXPECT_EQ(0.0f, grid[1][1][0]);
	EXPECT_EQ(0.0f, grid[2][1][0]);
	EXPECT_EQ(0.0f, grid[3][1][0]);
}

TEST(Grid3dTest, TestGetSet)
{
	Grid3d<1, 2, 4, float > grid(0.0f);
	grid[0][0][0] = 10.0f;
	EXPECT_EQ(10.0f, grid[0][0][0]);
}

TEST(Grid3dTest, TestEquals)
{
	Grid3d<1, 2, 4, float > grid1(0.0f);
	const Grid3d<1, 2, 4, float > grid2(0.0f);
	EXPECT_TRUE(grid1.equals(grid2));
	EXPECT_EQ(grid1, grid2);

	grid1[0][0][0] = 1.0f;
	EXPECT_FALSE(grid1.equals(grid2));
	EXPECT_NE(grid1, grid2);
}