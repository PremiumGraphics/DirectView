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