#include "gtest/gtest.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;

TEST(Image1dTest, TestConstruct)
{
	const Image1d<2, ColorRGBA<float> > image;
	EXPECT_EQ(2, image.size());
	EXPECT_EQ(ColorRGBA<float>::Black(), image[0]);
	EXPECT_EQ(ColorRGBA<float>::Black(), image[1]);
}

TEST(Image1dTest, TestConstructByColor)
{
	const Image1d<2> image( ColorRGBA<float>::White());
	EXPECT_EQ( ColorRGBA<float>::White(), image[0]);
	EXPECT_EQ( ColorRGBA<float>::White(), image[1]);
}

TEST(Image1dTest, TestGetSet)
{
	Image1d<2> image;
	EXPECT_EQ( ColorRGBA<float>::Black(), image.get(0) );
	image.set(0, ColorRGBA<float>::White() );
	EXPECT_EQ( ColorRGBA<float>::White(), image.get(0) );
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


TEST(Image3dTest, TestConstruct)
{
	const Image3d<1, 2, 4> image;
	EXPECT_EQ(1, image.sizex());
	EXPECT_EQ(2, image.sizey());
	EXPECT_EQ(4, image.sizez());
	EXPECT_EQ(8, image.size());
	EXPECT_EQ(ColorRGBA<float>::Black(), image[0][0][0]);
	EXPECT_EQ(ColorRGBA<float>::Black(), image[1][0][0]);
	EXPECT_EQ(ColorRGBA<float>::Black(), image[2][0][0]);
	EXPECT_EQ(ColorRGBA<float>::Black(), image[3][0][0]);
}

TEST(Image3dTest, TestOperatorGetSet)
{
	Image3d<2, 2, 2> image;
	EXPECT_EQ(ColorRGBA<float>::Black(), image[0][0][0]);

	image.set(0, 0, 0, ColorRGBA<float>::White());
	EXPECT_EQ(ColorRGBA<float>::White(), image[0][0][0]);
}

TEST(Image3dTest, TestEquals)
{
	Image3d<2, 2, 2> image1;
	Image3d<2, 2, 2> image2;

	EXPECT_TRUE(image1.equals(image2));
	EXPECT_EQ(image1, image2);

	image1[0][0][0] = ColorRGBA<float>::White();
	EXPECT_FALSE(image1.equals(image2));
	EXPECT_NE(image1, image2);
}