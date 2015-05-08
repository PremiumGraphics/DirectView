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
 
TEST( Vector2dTest, TestGetLengthFloat )
{
	Vector2d<float> v( 1.0f, 1.0f );

	const auto actual = v.getLength();
	const auto expected = std::sqrt(2.0f);

	EXPECT_FLOAT_EQ( expected, expected );
	EXPECT_FLOAT_EQ( expected, expected );
}

TEST(Vector2dTest, TestGetLengthDouble)
{
	Vector2d<double> v(1.0f, 1.0f);

	const auto actual = v.getLength();
	const auto expected = std::sqrt(2.0);

	EXPECT_DOUBLE_EQ(expected, expected);
}


TEST(Vector2dTest, TestGetLengthSquaredFloat)
{
	Vector2d<float> v(1.0, 1.0);

	const auto actual = v.getLengthSquared();
	const auto expected = 2.0f;

	EXPECT_FLOAT_EQ( expected, actual );
}

TEST(Vector2dTest, TestGetLengthSquaredDouble)
{
	Vector2d<double> v(1.0, 1.0);

	const auto actual = v.getLengthSquared();
	const auto expected = 2.0;

	EXPECT_DOUBLE_EQ( expected, actual );
}

TEST(Vector2dTest, TestGetDistanceFloat)
{
	Vector2d<float> v0(1.0f, 1.0f);
	Vector2d<float> v1(2.0f, 2.0f);
	const auto expected = std::sqrt(2.0f);

	EXPECT_FLOAT_EQ(expected, v0.getDistance(v1));
	EXPECT_FLOAT_EQ(expected, v1.getDistance(v0));
}

TEST(Vector2dTest, TestGetDistanceDouble)
{
	Vector2d<double> v0(1.0f, 1.0f);
	Vector2d<double> v1(2.0f, 2.0f);
	const auto expected = std::sqrt(2.0);

	EXPECT_DOUBLE_EQ(expected, v0.getDistance(v1));
	EXPECT_DOUBLE_EQ(expected, v1.getDistance(v0));
}