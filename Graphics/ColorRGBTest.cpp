#include "gtest/gtest.h"
 
#include "../Graphics/ColorRGB.h"

using namespace Crystal::Graphics;

template<class T>
class ColorRGBTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE( ColorRGBTest , TestTypes);

TYPED_TEST( ColorRGBTest, TestConstruct )
{
	ColorRGB<TypeParam> c;
	EXPECT_EQ( ColorRGB<TypeParam>::Black(), c );
	EXPECT_TRUE( c.isValid() );
}

TYPED_TEST( ColorRGBTest, EqualsTest )
{
	const ColorRGB<TypeParam>& c = ColorRGB<TypeParam>::Red();
	EXPECT_EQ( ColorRGB<TypeParam>::Red(), c );
	EXPECT_NE( ColorRGB<TypeParam>::Black(), c );
}

TYPED_TEST( ColorRGBTest, AddTest )
{
	ColorRGB<TypeParam> c = ColorRGB<TypeParam>( 1.0f, 0.0f, 0.0f );
	c.add( ColorRGB<TypeParam>( 0.0f, 1.0f, 1.0f ) );
	EXPECT_EQ( ColorRGB<TypeParam>::White(), c );
}

TYPED_TEST( ColorRGBTest, ToArray3Test )
{
	const ColorRGB<TypeParam>& c = ColorRGB<TypeParam>::Red();
	const std::vector<TypeParam>& values = c.toArray3();
	EXPECT_EQ( 3, values.size() );
	EXPECT_EQ( 1.0, values[0] );
	EXPECT_EQ( 0.0, values[1] );
	EXPECT_EQ( 0.0, values[2] );
}