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

TEST(Grid1dTest, TestGetSub)
{
	using T = float;
	const Grid1d<T> actual = Grid1d<T>(2, 0).getSub(0, 1);
	const Grid1d<T> expected(1, 0);
	EXPECT_EQ( expected, actual );
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
	const Grid2d<T> actual = Grid2d<T>(2, 2).getSub(0, 1, 0, 1);
	const Grid2d<T> expected(1, 1);
	EXPECT_EQ(expected, actual);
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
	const Grid3d<T> expected(1, 1, 1);
	EXPECT_EQ(expected, actual);
}

TEST(Grid3dTest, TestAdd)
{
	using T = float;
	auto lhs = Grid3d<T>(2, 2, 2).set( 0, 0, 0, 20 );
	const auto rhs = Grid3d<T>(2, 2, 2).set(1,1,1,10);
	lhs.add(rhs);

	const auto expected = Grid3d<T>(2, 2, 2).set(0, 0, 0, 20).set(1, 1, 1, 10);
	EXPECT_EQ(expected, lhs);
}
