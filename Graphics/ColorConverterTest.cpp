#include "gtest/gtest.h"

#include "ColorConverter.h"

using namespace Crystal::Graphics;

TEST( ColorConverterTest, TestToHSV )
{
	using T = float;
	EXPECT_EQ( ColorHSV<T>(   0, 1, 1 ), ColorConverter::toHSV( ColorRGB<T>::Red() ) );
	EXPECT_EQ( ColorHSV<T>( 120, 1, 1 ), ColorConverter::toHSV( ColorRGB<T>::Green() ) );
	EXPECT_EQ( ColorHSV<T>( 240, 1, 1 ), ColorConverter::toHSV( ColorRGB<T>::Blue() ) );
	EXPECT_EQ( ColorHSV<T>(   0, 0, 1 ), ColorConverter::toHSV( ColorRGB<T>::White() ) );
	EXPECT_EQ( ColorHSV<T>(   0, 0, 0 ), ColorConverter::toHSV( ColorRGB<T>::Black() ) );
}

TEST( ColorConverterTest, TestToRGB )
{
	using T = float;
	EXPECT_EQ( ColorRGB<T>::Red(),		ColorConverter::toRGB( ColorHSV<T>(   0, 1, 1 ) ) );
	EXPECT_EQ( ColorRGB<T>::Green(),	ColorConverter::toRGB( ColorHSV<T>( 120, 1, 1 ) ) );
	EXPECT_EQ( ColorRGB<T>::Blue(),		ColorConverter::toRGB( ColorHSV<T>( 240, 1, 1 ) ) );
	EXPECT_EQ( ColorRGB<T>::White(),	ColorConverter::toRGB( ColorHSV<T>(   0, 0, 1 ) ) );
	EXPECT_EQ( ColorRGB<T>::Black(),	ColorConverter::toRGB( ColorHSV<T>(   0, 0, 0 ) ) );
	ColorConverter::toRGB( ColorHSV<T>( 3, 1, 1 ) );
}