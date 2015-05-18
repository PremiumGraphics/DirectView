#include "gtest/gtest.h"

#include "../Math/Grid2d.h"

using namespace Crystal::Math;

TEST(Grid2dTest, TestConstruct)
{
	const Grid2d<1, 2, float> grid(0.0f);
	EXPECT_EQ(1, grid.sizex());
	EXPECT_EQ(2, grid.sizey());
	EXPECT_EQ(2, grid.size());

	EXPECT_EQ(0.0f, grid[0][0]);
	EXPECT_EQ(0.0f, grid[1][0]);
}

TEST(Grid2dTest, TestGetSet)
{
	Grid2d<2, 2, float> grid(0.0f);

	grid[0][0] = 100.0f;
	EXPECT_EQ( 100.0f, grid[0][0]);

}

TEST(Grid2dTest, TestEquals)
{
	Grid2d<2, 2, float> grid1(0.0f);
	Grid2d<2, 2, float> grid2(0.0f);
	EXPECT_TRUE(grid1.equals(grid2));
	EXPECT_EQ(grid1, grid2);

	grid1.set(0, 0, 100.0f);
	EXPECT_FALSE(grid1.equals(grid2));
	EXPECT_NE(grid1, grid2);
}