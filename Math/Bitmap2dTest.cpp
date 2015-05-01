#include "gtest/gtest.h"

#include "Bitmap2d.h"

using namespace Crystal::Math;


TEST(Bitmap2dTest, TestConstruct)
{
	const Bitmap2d<1> bitmap(1);
	EXPECT_EQ(bitmap.get1ds().size(), 1);
}

TEST(Bitmap2dTest, TestSize)
{
	EXPECT_EQ( Bitmap2d<1>(1).size(), 1);
	EXPECT_EQ( Bitmap2d<2>(2).size(), 4);
}

TEST(Bitmap2dTest, TestSet)
{
	Bitmap2d<1> bitmap(1);
	bitmap.set(0, 0);

	EXPECT_TRUE(bitmap[0][0]);
}

TEST(Bitmap2dTest, TestSetAll)
{
	Bitmap2d<2> bitmap(1);
	bitmap.set();

	EXPECT_TRUE(bitmap[0][0]);
	EXPECT_TRUE(bitmap[0][1]);
}


TEST(Bitmap2dTest, TestReset)
{
	Bitmap2d<1> bitmap(1);
	bitmap.set(0, 0);
	bitmap.reset(0, 0);

	EXPECT_FALSE(bitmap[0][0]);
}

TEST(Bitmap2dTest, TestAll)
{
	Bitmap2d<2> bitmap(2);
	bitmap.set(0, 0);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(0, 1);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(1, 0);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(1, 1);
	EXPECT_TRUE(bitmap.all());
}

TEST(Bitmap2dTest, TestNone)
{
	Bitmap2d<2> bitmap(2);
	EXPECT_TRUE( bitmap.none());
	bitmap.set(0, 0);
	EXPECT_FALSE(bitmap.none());
}
