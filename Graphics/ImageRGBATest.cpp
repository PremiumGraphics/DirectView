#include "gtest/gtest.h"
 
#include "../Graphics/ImageRGBA.h"

using namespace Crystal::Graphics;

TEST( ImageRGBATest, ContructTest )
{
	ImageRGBA<float> image;
	EXPECT_EQ( 0, image.getWidth() );
	EXPECT_EQ( 0, image.getHeight() );
	//EXPECT_TRUE( image.getValues().empty() );
}

TEST( ImageRGBATest, TestColor )
{
	ImageRGBA<float> color( 1, 1);
	color.setColor(0, 0, ColorRGBA<float>::Red() );
	EXPECT_EQ( ColorRGBA<float>::Red(), color.getColor(0, 0) );
}
