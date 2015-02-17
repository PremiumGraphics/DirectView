#include "gtest/gtest.h"

#include "ColorConverter.h"

using namespace Crystal::Graphics;

TEST( ColorConverterTest, TestToHSV )
{
	EXPECT_EQ( ColorHSV(   0.0, 1.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::Red() ) );
	EXPECT_EQ( ColorHSV( 120.0, 1.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::Green() ) );
	EXPECT_EQ( ColorHSV( 240.0, 1.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::Blue() ) );
	EXPECT_EQ( ColorHSV(   0.0, 0.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::White() ) );
	EXPECT_EQ( ColorHSV(   0.0, 0.0, 0.0 ), ColorConverter::toHSV( ColorRGB<float>::Black() ) );
}

TEST( ColorConverterTest, TestToRGB )
{
	EXPECT_EQ( ColorRGB<float>::Red(),		ColorConverter::toRGB( ColorHSV(   0.0, 1.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::Green(),	ColorConverter::toRGB( ColorHSV( 120.0, 1.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::Blue(),		ColorConverter::toRGB( ColorHSV( 240.0, 1.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::White(),	ColorConverter::toRGB( ColorHSV(   0.0, 0.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::Black(),	ColorConverter::toRGB( ColorHSV(   0.0, 0.0, 0.0 ) ) );
	ColorConverter::toRGB( ColorHSV( 3.0, 1.0, 1.0 ) );
}