#include "gtest/gtest.h"

#include "Bitmap2d.h"

using namespace Crystal::Math;


TEST(Bitmap2dTest, TestConstruct)
{
	const Bitmap2d<1,1> bitmap;
}


TEST(Bitmap2dTest, TestSize)
{
	{
		const Bitmap2d<1, 1> bitmap;
		EXPECT_EQ(bitmap.size(), 1);
	}
	{
		const Bitmap2d<2, 2> bitmap;
		EXPECT_EQ(bitmap.size(), 4);
	}
}

TEST(Bitmap2dTest, TestSizeX)
{
	{
		const Bitmap2d<1, 2> bitmap;
		EXPECT_EQ(bitmap.sizex(), 1);
	}
	{
		const Bitmap2d<2, 4> bitmap;
		EXPECT_EQ(bitmap.sizex(), 2);
	}
}

TEST(Bitmap2dTest, TestSizeY)
{
	{
		const Bitmap2d<1, 2> bitmap;
		EXPECT_EQ(bitmap.sizey(), 2);
	}

	{
		const Bitmap2d<2, 4> bitmap;
		EXPECT_EQ(bitmap.sizey(), 4);
	}
}

TEST(Bitmap2dTest, TestSet)
{
	Bitmap2d<2,2> bitmap;
	EXPECT_FALSE(bitmap[0][0]);
	bitmap.set(0, 0);
	EXPECT_TRUE( bitmap[0][0]);
	bitmap.set(0, 1);
	EXPECT_TRUE( bitmap[0][1]);
}

TEST(Bitmap2dTest, TestSetAll)
{
	Bitmap2d<2, 1> bitmap;
	bitmap.set();

	EXPECT_TRUE(bitmap[0][0]);
	EXPECT_TRUE(bitmap[0][1]);
}

TEST(Bitmap2dTest, TestSet1d)
{
	Bitmap2d<2, 2> bitmap;
	bitmap.set(0, Bitmap1d<2>("01"));
	EXPECT_TRUE( bitmap[0][0]);
	EXPECT_FALSE(bitmap[0][1]);
}

TEST(Bitmap2dTest, TestReset)
{
	Bitmap2d<1,1> bitmap;
	bitmap.set(0, 0);
	bitmap.reset(0, 0);

	EXPECT_FALSE(bitmap[0][0]);
}

TEST(Bitmap2dTest, TestToString)
{
	Bitmap2d<2, 2> bitmap;
	EXPECT_EQ("0000", bitmap.toString());
	bitmap.set(0, 0);
	EXPECT_EQ("0100", bitmap.toString());
	bitmap.set(0, 1);
	EXPECT_EQ("1100", bitmap.toString());
}


TEST(Bitmap2dTest, TestEquals)
{
	Bitmap2d<1, 1> bmp1;
	Bitmap2d<1, 1> bmp2;

	EXPECT_TRUE( bmp1.equals(bmp2) );
	bmp1.set(0, 0);
	EXPECT_FALSE(bmp1.equals(bmp2));
}


TEST(Bitmap2dTest, TestAll)
{
	Bitmap2d<2,2> bitmap;
	bitmap.set(0, 0);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(0, 1);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(1, 0);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(1, 1);
	EXPECT_TRUE( bitmap.all());
}

TEST(Bitmap2dTest, TestNone)
{
	Bitmap2d<2,2> bitmap;
	bitmap.set();

	EXPECT_FALSE( bitmap.none());
	bitmap.reset(0, 0);
	EXPECT_FALSE( bitmap.none());
	bitmap.reset(0, 1);
	EXPECT_FALSE( bitmap.none());
	bitmap.reset(1, 0);
	EXPECT_FALSE( bitmap.none());
	bitmap.reset(1, 1);
	EXPECT_TRUE(  bitmap.none());
}

TEST(Bitmap2dTest, TestResetAll)
{
	Bitmap2d<2,2> bitmap;
	bitmap.set(0, 0);
	bitmap.reset();

	EXPECT_TRUE(bitmap.none());
}

TEST(Bitmap2dTest, TestOperatorOr)
{
	Bitmap2d<2, 2> bmp1;
	bmp1.set(0, 0);
	bmp1.set(0, 1);

	Bitmap2d<2, 2> bmp2;
	bmp2.set(0, 0);

	bmp1 |= bmp2;
	EXPECT_TRUE(bmp1[0][0]);
	EXPECT_TRUE(bmp1[0][1]);
}


TEST(Bitmap2dTest, TestOperatorAnd)
{
	Bitmap2d<2, 2> bmp1;
	bmp1.set(0, 0);
	bmp1.set(0, 1);

	Bitmap2d<2, 2> bmp2;
	bmp2.set(0, 0);

	bmp1 &= bmp2;
	EXPECT_TRUE( bmp1[0][0]);
	EXPECT_FALSE(bmp1[0][1]);
}
