#include "gtest/gtest.h"

#include "../Math/Vector1d.h"

using namespace Crystal::Math;

template<class T>
class Vector1dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Vector1dTest, TestTypes);

TYPED_TEST(Vector1dTest, TestGetLength)
{
	EXPECT_EQ( 0.0, Vector1d<TypeParam>(0.0).getLength() );
	EXPECT_EQ( 4.0, Vector1d<TypeParam>(1.0, Vector1d<TypeParam>(5.0) ).getLength());

}
template<class T>
class Vector2dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Vector2dTest, TestTypes);

TYPED_TEST(Vector2dTest, ScaleTest)
{
	Vector2d<TypeParam> v(1.0f, 1.0f);
	const Vector2d<TypeParam>& scaled = v.getScaled(2.0);
	EXPECT_EQ(Vector2d<TypeParam>(2.0, 2.0), scaled);
}

TYPED_TEST(Vector2dTest, TestGetLength)
{
	const auto actual = Vector2d<TypeParam>(1.0f, 1.0f).getLength();
	const auto expected = std::sqrt(TypeParam(2));

	EXPECT_TRUE( Tolerance<TypeParam>::isEqualLoosely( actual, expected ) );
}

TYPED_TEST(Vector2dTest, TestGetLengthSquaredFloat)
{
	const auto actual = Vector2d<TypeParam>(1,1).getLengthSquared();
	const TypeParam expected = 2;

	EXPECT_TRUE( Tolerance<TypeParam>::isEqualLoosely(expected, actual ));
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

/*
TEST(Vector2dTest, TestGetLengthFloat)
{
	Vector2d<float> v(1.0f, 1.0f);

	const auto actual = v.getLength();
	const auto expected = std::sqrt(2.0f);

	EXPECT_FLOAT_EQ(expected, expected);
	EXPECT_FLOAT_EQ(expected, expected);
}
*/