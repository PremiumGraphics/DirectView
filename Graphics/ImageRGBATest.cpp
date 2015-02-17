#include "gtest/gtest.h"
 
#include "../Graphics/ImageRGBA.h"

using namespace Crystal::Graphics;

TEST( ImageRGBATest, ContructTest )
{
	ImageRGBA<unsigned int> image;
	EXPECT_EQ( 0, image.getWidth() );
	EXPECT_EQ( 0, image.getHeight() );
	//EXPECT_TRUE( image.getValues().empty() );
}

TEST( ImageRGBATest, TestColor )
{
	ImageRGBA<unsigned int> color( 1, 1);
	color.setColor(0, 0, ColorRGBA<unsigned int>::Red() );
	EXPECT_EQ( ColorRGBA<unsigned int>::Red(), color.getColor(0, 0) );
}
