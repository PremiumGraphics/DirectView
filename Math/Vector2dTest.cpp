#include "gtest/gtest.h"
 
#include "../Math/Vector2d.h"
#include "../Math/Matrix2d.h"

using namespace Crystal::Math;

template<class T>
class Vector2dTest : public testing::Test {
};

typedef ::testing::Types<float,double> TestTypes;

TYPED_TEST_CASE( Vector2dTest , TestTypes);

TYPED_TEST( Vector2dTest, ScaleTest )
{
	Vector2d<TypeParam> v( 1.0f, 1.0f );
	const Vector2d<TypeParam>& scaled = v.getScaled( 2.0 );
	EXPECT_EQ( Vector2d<TypeParam>( 2.0, 2.0 ), scaled );
}
 
TYPED_TEST( Vector2dTest, SqrtTest )
{
	Vector2d<TypeParam> v( 1.0, 1.0 );
	//EXPECT_FALSE( Tolerances::isEqualLoosely( v.getLength(), std::sqrt( 1.99 ) ) );

	EXPECT_FLOAT_EQ( v.getLength(), std::sqrt( 2.0f ) );
	EXPECT_FLOAT_EQ( v.getLength(), std::sqrt( 2.0f ) );

	EXPECT_FLOAT_EQ( v.getLengthSquared(), 2.0f );
	EXPECT_FLOAT_EQ( v.getLengthSquared(), 2.0f );

}
 
TYPED_TEST( Vector2dTest, LengthTest )
{
	Vector2d<TypeParam> v0( 1.0f, 1.0f );
	Vector2d<TypeParam> v1( 2.0f, 2.0f );
	EXPECT_FLOAT_EQ( v0.getDistance( v1 ), std::sqrt( 2.0f ) );
	EXPECT_FLOAT_EQ( v0.getDistance( v1 ), std::sqrt( 2.0f ) );
}