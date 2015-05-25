#include "gtest/gtest.h"

#include "ColorConverter.h"

using namespace Crystal::Graphics;

TEST( ColorConverterTest, TestToHSV )
{
	using T = float;
	EXPECT_EQ( ColorHSV<T>( 0.0, 1.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::Red() ) );
	EXPECT_EQ( ColorHSV<T>( 120.0, 1.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::Green() ) );
	EXPECT_EQ( ColorHSV<T>( 240.0, 1.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::Blue() ) );
	EXPECT_EQ( ColorHSV<T>(   0.0, 0.0, 1.0 ), ColorConverter::toHSV( ColorRGB<float>::White() ) );
	EXPECT_EQ( ColorHSV<T>(   0.0, 0.0, 0.0 ), ColorConverter::toHSV( ColorRGB<float>::Black() ) );
}

TEST( ColorConverterTest, TestToRGB )
{
	using T = float;
	EXPECT_EQ( ColorRGB<float>::Red(),		ColorConverter::toRGB( ColorHSV<T>(   0.0, 1.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::Green(),	ColorConverter::toRGB( ColorHSV<T>( 120.0, 1.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::Blue(),		ColorConverter::toRGB( ColorHSV<T>( 240.0, 1.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::White(),	ColorConverter::toRGB( ColorHSV<T>(   0.0, 0.0, 1.0 ) ) );
	EXPECT_EQ( ColorRGB<float>::Black(),	ColorConverter::toRGB( ColorHSV<T>(   0.0, 0.0, 0.0 ) ) );
	ColorConverter::toRGB( ColorHSV<T>( 3.0, 1.0, 1.0 ) );
}