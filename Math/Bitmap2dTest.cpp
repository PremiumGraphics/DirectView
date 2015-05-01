#include "gtest/gtest.h"

#include "Bitmap2d.h"

using namespace Crystal::Math;


TEST(Bitmap2dTest, TestConstruct)
{
	const Bitmap2d<1> bitmap(1);
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

TEST(Bitmap2dTest, TestNone)
{
	EXPECT_TRUE( Bitmap2d<2>(2).none());
	Bitmap2d<2> bitmap(2);
	bitmap.set(0, 0);
	EXPECT_FALSE(bitmap.none());
}

TEST(Bitmap3dTest, TestConstruct)
{
	EXPECT_EQ( Bitmap3d<1>(1,1).size(), 1);
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
