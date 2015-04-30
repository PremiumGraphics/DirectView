#include "gtest/gtest.h"

#include "Bitmap1d.h"

using namespace Crystal::Math;

TEST(Bitmap1dTest, TestConstruct)
{
	Bitmap1d<1> bitmap;
	EXPECT_EQ(1, bitmap.size());
	EXPECT_FALSE(bitmap[0]);
	//bitmap[10] = true;
}

TEST(Bitmap1dTest, TestSet)
{
	Bitmap1d<1> bitmap(1);
	bitmap.set(0);

	EXPECT_TRUE(bitmap[0]);
}

TEST(Bitmap2dTest, TestConstruct)
{
	Bitmap2d<1> bitmap(1);
	EXPECT_EQ(bitmap.get1ds().size(), 1);

	EXPECT_FALSE(bitmap[0][0]);
}

TEST(Bitmap2dTest, TestSet)
{
	Bitmap2d<1> bitmap(1);
	bitmap.set(0, 0);

	EXPECT_TRUE(bitmap[0][0]);
}

TEST(Bitmap3dTest, TestConstruct)
{
	Bitmap3d<1> bitmap(1);
	EXPECT_EQ(bitmap.size(), 1);
}