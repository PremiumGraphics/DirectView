#include "gtest/gtest.h"

#include "../Math/Vector.h"

using namespace Crystal::Math;

template<class T>
class VectorTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(VectorTest, TestTypes);


TYPED_TEST(VectorTest, ScaleTest)
{
	EXPECT_EQ( Vector2d < TypeParam >({ 2.0, 2.0 }), Vector2d<TypeParam>({ 1, 1 }).getScaled(2));
}

TYPED_TEST(VectorTest, TestGetLength)
{
	using T = TypeParam;
	EXPECT_EQ( 0, Vector1d<T>({ 0 }).getLength());

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(std::sqrt(TypeParam(2)), Vector2d<TypeParam>({ 1, 1 }).getLength() ) );

	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(3, Vector3d__<T>({ 1, 1, 1 }).getLengthSquared()));
	EXPECT_TRUE(Tolerance<T>::isEqualStrictly(3, Vector3d__<T>({ 1, 1, 1 }).getLengthSquared()));

	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(14, Vector3d__<T>({ 1, 2, 3 }).getLengthSquared()));
	EXPECT_TRUE(Tolerance<T>::isEqualStrictly(14, Vector3d__<T>({ 1, 2, 3 }).getLengthSquared()));
}



TYPED_TEST(VectorTest, TestGetLengthSquared)
{
	const auto actual = Vector2d<TypeParam>({ 1, 1 }).getLengthSquared();
	const TypeParam expected = 2;

	EXPECT_TRUE( Tolerance<TypeParam>::isEqualLoosely(expected, actual ));
}

TYPED_TEST(VectorTest, TestGetDistance)
{
	using T = TypeParam;
	Vector2d<T> v0({ 1.0f, 1.0f });
	Vector2d<T> v1({ 2.0f, 2.0f });
	const auto expected = std::sqrt(2.0f);

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( std::sqrt(T(2)), v0.getDistance(v1)) );
	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(std::sqrt(T(2)), v1.getDistance(v0)));

	//EXPECT_TRUE(expected, v1.getDistance(v0));
}