#include "gtest/gtest.h"

#include "Bitmap3d.h"

using namespace Crystal::Math;

TEST(Bitmap3dTest, TestConstruct)
{
	const auto actual = Bitmap3d<1, 1>(1).size();
	EXPECT_EQ( actual, 1);
}

TEST(Bitmap3dTest, TestSize)
{
	const auto actual = Bitmap3d<2, 2>(2).size();
 	EXPECT_EQ( actual, 8);
}

TEST(Bitmap3dTest, TestSizeX)
{
	const auto actual = Bitmap3d<1, 4>(2).sizex();
	EXPECT_EQ( actual, 1);
}

TEST(Bitmap3dTest, TestSizeY)
{
	const auto actual = Bitmap3d<1, 4>(2).sizey();
	EXPECT_EQ( actual, 2);
}

TEST(Bitmap3dTest, TestSizeZ)
{
	const auto actual = Bitmap3d<1, 4>(2).sizez();
	EXPECT_EQ(actual, 4);
}

TEST(Bitmap3dTest, TestSet)
{
	Bitmap3d<2, 2> bitmap(2);
	bitmap.set(0, 0, 0);

	EXPECT_TRUE(bitmap[0][0][0]);

	bitmap.set(0, 1, 0);
	EXPECT_TRUE(bitmap[0][1][0]);

}

TEST(Bitmap3dTest, TestReset)
{
	Bitmap3d<2, 2> bitmap(2);
	bitmap.reset(0, 0, 0);

	EXPECT_FALSE(bitmap[0][0][0]);
}
