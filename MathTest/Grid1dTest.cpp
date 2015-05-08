#include "gtest/gtest.h"

#include "../Math/Grid1d.h"

using namespace Crystal::Math;

TEST(Grid1dTest, TestConstruct)
{
	const Grid1d<2, float > grid(0.0f);
	EXPECT_EQ(2, grid.size());
	EXPECT_EQ( 0.0f, grid[0]);
	EXPECT_EQ( 0.0f, grid[1]);
}

TEST(Image1dTest, TestGetSet)
{
	Grid1d<2, float > grid(0.0f);
	grid.set(0, 100.0f);
	
	EXPECT_EQ( 100.0f, grid.get(0) );
	grid.set(1, 200.0f);
	EXPECT_EQ( 200.0f, grid.get(1) );
}


/*
TEST(Image1dTest, TestConstructByColor)
{
	const Image1d<2> image(ColorRGBA<float>::White());
	EXPECT_EQ(ColorRGBA<float>::White(), image[0]);
	EXPECT_EQ(ColorRGBA<float>::White(), image[1]);
}

TEST(Image1dTest, TestGetSet)
{
	Image1d<2> image;
	EXPECT_EQ(ColorRGBA<float>::Black(), image.get(0));
	image.set(0, ColorRGBA<float>::White());
	EXPECT_EQ(ColorRGBA<float>::White(), image.get(0));
	image[1] = ColorRGBA<float>::White();
	EXPECT_EQ(ColorRGBA<float>::White(), image.get(1));

}

TEST(Image1dTest, TestEquals)
{
	Image1d<2> image1;
	Image1d<2> image2;
	EXPECT_TRUE(image1.equals(image2));
	EXPECT_EQ(image1, image2);
	image1.set(0, ColorRGBA<float>::White());
	EXPECT_FALSE(image1.equals(image2));
	EXPECT_NE(image1, image2);
}
*/