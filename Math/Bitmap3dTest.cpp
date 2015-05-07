#include "gtest/gtest.h"

#include "Bitmap3d.h"

using namespace Crystal::Math;

TEST(Bitmap3dTest, TestConstruct)
{
	Bitmap3d<1, 1, 1> bitmap;
	EXPECT_EQ( bitmap.size(), 1);
}

TEST(Bitmap3dTest, TestSize)
{
	Bitmap3d<2, 2, 2> bitmap;
 	EXPECT_EQ( bitmap.size(), 8);
}

TEST(Bitmap3dTest, TestSizeX)
{
	Bitmap3d<1, 2, 4> bitmap;
	const auto actual = bitmap.sizex();
	EXPECT_EQ( actual, 1);
}

TEST(Bitmap3dTest, TestSizeY)
{
	Bitmap3d<1, 2, 4> bitmap;
	const auto actual = bitmap.sizey();
	EXPECT_EQ( actual, 2);
}

TEST(Bitmap3dTest, TestSizeZ)
{
	Bitmap3d<1, 2, 4> bitmap;
	const auto actual = bitmap.sizez();
	EXPECT_EQ(actual, 4);
}

TEST(Bitmap3dTest, TestSet)
{
	Bitmap3d<2, 2, 2> bitmap;
	bitmap.set(0, 0, 0);

	EXPECT_TRUE(bitmap[0][0][0]);

	bitmap.set(0, 1, 0);
	EXPECT_TRUE(bitmap[0][1][0]);

}

TEST(Bitmap3dTest, TestReset)
{
	Bitmap3d<2, 2, 2> bitmap;
	bitmap.reset(0, 0, 0);

	EXPECT_FALSE(bitmap[0][0][0]);
}

TEST(Bitmap3dTest, TestToString)
{
	Bitmap3d<2, 2, 2> bitmap;

	EXPECT_EQ( "00000000", bitmap.toString() );
}

TEST(Bitmap3dTest, TestEquals)
{
	Bitmap3d<2, 2, 2> bmp1;
	Bitmap3d<2, 2, 2> bmp2;

	EXPECT_TRUE(bmp1.equals(bmp2));
	bmp1.set(0, 0, 0);
	EXPECT_FALSE(bmp1.equals(bmp2));
}