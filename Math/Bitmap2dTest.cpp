#include "gtest/gtest.h"

#include "Bitmap2d.h"

using namespace Crystal::Math;


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

TEST(Bitmap2dTest, TestReset)
{
	Bitmap2d<1> bitmap(1);
	bitmap.set(0, 0);
	bitmap.reset(0, 0);

	EXPECT_FALSE(bitmap[0][0]);
}


TEST(Bitmap3dTest, TestConstruct)
{
	Bitmap3d<1> bitmap(1,1);
	EXPECT_EQ(bitmap.size(), 1);
}

TEST(Bitmap3dTest, TestSet)
{
	Bitmap3d<1> bitmap(1,1);
	bitmap.set(0, 0, 0);

	EXPECT_TRUE(bitmap[0][0][0]);
}

TEST(Bitmap3dTest, TestReset)
{
	Bitmap3d<1> bitmap(1, 1);
	bitmap.reset(0, 0, 0);

	EXPECT_FALSE(bitmap[0][0][0]);
}
