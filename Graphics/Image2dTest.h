#include "gtest/gtest.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;

TEST(Image2dTest, TestConstruct)
{
	const Image2d<1, 2> image;
	EXPECT_EQ(1, image.sizex());
	EXPECT_EQ(2, image.sizey());
	EXPECT_EQ(2, image.size());
	EXPECT_EQ(ColorRGBA<float>::Black(), image[0][0]);
	EXPECT_EQ(ColorRGBA<float>::Black(), image[1][0]);
}

TEST(Image2dTest, TestGetSet)
{
	Image2d<2, 2> image;
	EXPECT_EQ(ColorRGBA<float>::Black(), image[0][0]);

	image.set(0, 0, ColorRGBA<float>::White());
	EXPECT_EQ(ColorRGBA<float>::White(), image[0][0]);

	image[0][1] = ColorRGBA<float>::Black();
	EXPECT_EQ(ColorRGBA<float>::Black(), image[0][1]);
}

TEST(Image2dTest, TestEquals)
{
	Image2d<2, 2> image1;
	Image2d<2, 2> image2;
	EXPECT_TRUE(image1.equals(image2));
	EXPECT_EQ(image1, image2);
	image1.set(0, 0, ColorRGBA<float>::White());
	EXPECT_FALSE(image1.equals(image2));
	EXPECT_NE(image1, image2);
}
