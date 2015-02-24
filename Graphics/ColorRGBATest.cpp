#include "gtest/gtest.h"
 
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

template<class T>
class ColorRGBATest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE( ColorRGBATest , TestTypes);

TYPED_TEST( ColorRGBATest, TestEquals )
{
	const ColorRGBA<TypeParam>& c = ColorRGBA<TypeParam>::Red();
	EXPECT_EQ( ColorRGBA<TypeParam>::Red(),   c );
	EXPECT_NE( ColorRGBA<TypeParam>::Black(), c );
}

TYPED_TEST( ColorRGBATest, TestAdd )
{
	ColorRGBA<TypeParam> c = ColorRGBA<TypeParam>::Red();
	c.add( ColorRGBA<TypeParam>::Green() );
	EXPECT_EQ( 1.0, c.getRed() );
	EXPECT_EQ( 1.0, c.getGreen() );
	EXPECT_EQ( 0.0, c.getBlue() );
	EXPECT_EQ( 0.0, c.getAlpha() );
}

TYPED_TEST( ColorRGBATest, TestAddOperator )
{
	ColorRGBA<TypeParam> c = ColorRGBA<TypeParam>::Red();
	c += ColorRGBA<TypeParam>::Green();
	c += ColorRGBA<TypeParam>::Blue();
	EXPECT_EQ( ColorRGBA<TypeParam>::White(), c );
}

TYPED_TEST( ColorRGBATest, TestAdded )
{
	const ColorRGBA<TypeParam>& c1 = ColorRGBA<TypeParam>::Red();
	const ColorRGBA<TypeParam>& c2 = ColorRGBA<TypeParam>::Green();
	const ColorRGBA<TypeParam>& actual = c1.getAdded( c2 );
	EXPECT_EQ( 1.0, actual.getRed() );
	EXPECT_EQ( 1.0, actual.getGreen() );
	EXPECT_EQ( 0.0, actual.getBlue() );
	EXPECT_EQ( 0.0, actual.getAlpha() );
}

TYPED_TEST( ColorRGBATest, TestAddedOperator )
{
	const ColorRGBA<TypeParam>& c1 = ColorRGBA<TypeParam>::Red();
	const ColorRGBA<TypeParam>& c2 = ColorRGBA<TypeParam>::Green();
	const ColorRGBA<TypeParam>& c3 = ColorRGBA<TypeParam>::Blue();
	EXPECT_EQ( ColorRGBA<TypeParam>::White(), c1 + c2 + c3 );
}

TYPED_TEST( ColorRGBATest, TestToArray3 )
{
	const ColorRGBA<TypeParam> c = ColorRGBA<TypeParam>::Red();
	const std::vector<TypeParam>& actual = c.toArray3();
	const std::vector<TypeParam> expected{ 1.0, 0.0, 0.0 };
	EXPECT_EQ( expected, actual );
}

TYPED_TEST( ColorRGBATest, TestToArray4 )
{
	const ColorRGBA<TypeParam>& c = ColorRGBA<TypeParam>::Red();
	const std::vector<TypeParam>& actual = c.toArray4();
	const std::vector<TypeParam> expected{ 1.0, 0.0, 0.0, 0.0 };
	EXPECT_EQ( expected, actual );
}