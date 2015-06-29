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

TEST(Grid1dTest, TestSet)
{
	using T = float;
	Grid1d<T> lhs(2, 10);
	lhs.set(1, Grid1d<T>(1, 20));
	EXPECT_EQ(20, lhs.get(1));
}

TEST(Grid1dTest, TestGetSub)
{
	using T = float;
	EXPECT_EQ(Grid1d<T>(1, 0), Grid1d<T>(2, 0).getSub(0, 1));
	EXPECT_EQ(Grid1d<T>(2, 100), Grid1d<T>(5, 100).getSub(0, 2));

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

TEST(Grid2dTest, TestGetSub)
{
	using T = float;
	EXPECT_EQ( Grid2d<T>(1, 1), Grid2d<T>(2, 2).getSub(0, 1, 0, 1) );
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

TEST(Grid3dTest, TestToArray8)
{
	using T = float;
	std::array<T, 8> expected{ 0, 0, 0, 0, 0, 0, 0, 0 };
	EXPECT_EQ( expected, Grid3d<T>(2, 2, 2).toArray8(0,0,0));
}

TEST(Grid3dTest, TestGetSub)
{
	using T = float;
	const Grid3d<T> actual = Grid3d<T>(2, 2, 2).getSub({ 0, 0, 0 }, { 1, 1, 1 });
	
	EXPECT_EQ( Grid3d<T>(1, 1, 1) , actual);
}

TEST(Grid3dTest, TestAdd)
{
	using T = float;
	auto lhs = Grid3d<T>(2, 2, 2);
	lhs.set(0, 0, 0, 20);
	auto rhs = Grid3d<T>(2, 2, 2);
	rhs.set(1, 1, 1, 10);
	lhs.add(rhs);

	auto expected = Grid3d<T>(2, 2, 2);
	expected.set(0, 0, 0, 20);
	expected.set(1, 1, 1, 10);
	EXPECT_EQ(expected, lhs);
}

TEST(Grid3dTest, TestSub)
{
	using T = float;
	auto lhs = Grid3d<T>(2, 2, 2);
	lhs.set(0, 0, 0, 20);
	auto rhs = Grid3d<T>(2, 2, 2);
	rhs.set(1, 1, 1, -10);
	lhs.add(rhs);

	auto expected = Grid3d<T>(2, 2, 2);
	expected.set(0, 0, 0, 20);
	expected.set(1, 1, 1, -10);
	EXPECT_EQ(expected, lhs);
}

TEST(Grid3dTest, TestIsLower)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2);
	grid.set(0, 0, 0, 10);
	const T threshold = 5;
	EXPECT_FALSE(grid.isLower(0, 0, 0, threshold));
	EXPECT_TRUE( grid.isLower(1, 0, 0, threshold));
}

TEST(Grid3dTest, TestIsAllLower)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2);
	const T threshold = 5;

	EXPECT_TRUE(grid.isAllLower(0, 0, 0, threshold));
	grid.set(0, 0, 0, 10);
	EXPECT_FALSE( grid.isAllLower(0, 0, 0, threshold) );
}

/*
TEST(Grid3dTest, TestIsBoundary)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2);
	grid.set(0, 0, 0, 10);
	const T threshold = 5;
	grid.
}
*/