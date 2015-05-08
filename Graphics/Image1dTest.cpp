#include "gtest/gtest.h"

#include "../Graphics/Image1d.h"

using namespace Crystal::Graphics;

TEST(Image1dTest, TestConstruct)
{
	const Image1d<2> image;
	EXPECT_EQ(2, image.size());
}

TEST(Image1dTest, TestOperatorGet)
{
	const Image1d<2> image;
	EXPECT_EQ( ColorRGBA<float>::Black(), image[0] );
}

TEST(Image2dTest, TestConstruct)
{
	const Image2d<2,2> image;
	EXPECT_EQ(4, image.size());
}
