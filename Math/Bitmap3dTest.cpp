#include "gtest/gtest.h"

#include "Bitmap3d.h"

using namespace Crystal::Math;

TEST(Bitmap3dTest, TestConstruct)
{
	EXPECT_EQ(Bitmap3d<1>(1, 1).size(), 1);
}

TEST(Bitmap3dTest, TestSize)
{
	EXPECT_EQ(Bitmap3d<2>(2, 2).size(), 8);
}

TEST(Bitmap3dTest, TestSize2d)
{
	EXPECT_EQ(Bitmap3d<1>(2, 4).size2d(), 2);
}

TEST(Bitmap3dTest, TestSize3d)
{
	EXPECT_EQ(Bitmap3d<1>(2, 4).size3d(), 4);
}

TEST(Bitmap3dTest, TestSet)
{
	Bitmap3d<1> bitmap(1, 1);
	bitmap.set(0, 0, 0);

	EXPECT_TRUE(bitmap[0][0][0]);
}

TEST(Bitmap3dTest, TestReset)
{
	Bitmap3d<1> bitmap(1, 1);
	bitmap.reset(0, 0, 0);

	EXPECT_FALSE(bitmap[0][0][0]);
}
