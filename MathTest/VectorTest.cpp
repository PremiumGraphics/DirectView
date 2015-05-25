#include "gtest/gtest.h"

#include "../Math/Vector1d.h"

using namespace Crystal::Math;

template<class T>
class VectorTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(VectorTest, TestTypes);


TYPED_TEST(VectorTest, ScaleTest)
{
	Vector2d<TypeParam> v({ 1.0f, 1.0f });
	const Vector2d<TypeParam>& scaled = v.getScaled(2.0);
	EXPECT_EQ( Vector2d < TypeParam >( {2.0, 2.0} ), scaled);
}

TYPED_TEST(VectorTest, TestGetLength)
{
	EXPECT_EQ(0.0, Vector1d<TypeParam>(0.0).getLength());

	const auto actual = Vector2d<TypeParam>({ 1.0f, 1.0f }).getLength();
	const auto expected = std::sqrt(TypeParam(2));

	EXPECT_TRUE( Tolerance<TypeParam>::isEqualLoosely( actual, expected ) );
}

TYPED_TEST(VectorTest, TestGetLengthSquaredFloat)
{
	const auto actual = Vector2d<TypeParam>({ 1, 1 }).getLengthSquared();
	const TypeParam expected = 2;

	EXPECT_TRUE( Tolerance<TypeParam>::isEqualLoosely(expected, actual ));
}

TEST(VectorTest, TestGetDistanceFloat)
{
	Vector2d<float> v0({ 1.0f, 1.0f });
	Vector2d<float> v1({ 2.0f, 2.0f });
	const auto expected = std::sqrt(2.0f);

	EXPECT_FLOAT_EQ(expected, v0.getDistance(v1));
	EXPECT_FLOAT_EQ(expected, v1.getDistance(v0));
}

TEST(VectorTest, TestGetDistanceDouble)
{
	Vector2d<double> v0({ 1.0f, 1.0f });
	Vector2d<double> v1({ 2.0f, 2.0f });
	const auto expected = std::sqrt(2.0);

	EXPECT_DOUBLE_EQ(expected, v0.getDistance(v1));
	EXPECT_DOUBLE_EQ(expected, v1.getDistance(v0));
}

/*
TEST(VectorTest, TestGetLengthFloat)
{
	Vector2d<float> v(1.0f, 1.0f);

	const auto actual = v.getLength();
	const auto expected = std::sqrt(2.0f);

	EXPECT_FLOAT_EQ(expected, expected);
	EXPECT_FLOAT_EQ(expected, expected);
}
*/