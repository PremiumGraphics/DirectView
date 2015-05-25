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

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(std::sqrt(T(2)), Vector2d<T>({ 1, 1 }).getLength() ) );

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(3, Vector3d__<T>({ 1, 1, 1 }).getLengthSquared()));
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(3, Vector3d__<T>({ 1, 1, 1 }).getLengthSquared()));

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(14, Vector3d__<T>({ 1, 2, 3 }).getLengthSquared()));
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(14, Vector3d__<T>({ 1, 2, 3 }).getLengthSquared()));
}



TYPED_TEST(VectorTest, TestGetLengthSquared)
{
	EXPECT_TRUE(Tolerance<TypeParam>::isEqualLoosely( 2, Vector2d<TypeParam>({ 1, 1 }).getLengthSquared()));
}

TYPED_TEST(VectorTest, TestGetDistanceSquared)
{
	using T = TypeParam;

	EXPECT_TRUE(Tolerance<T>::isEqualLoosely( 2, Vector2d<T>({ 1, 1 }).getDistanceSquared(Vector2d< T >({ 2, 2 }))));
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely( 2, Vector2d<T>({ 2, 2 }).getDistanceSquared(Vector2d<T>({ 1, 1 }))));

	EXPECT_TRUE(Tolerance<T>::isEqualLoosely( 3, Vector3d__<T>({ 1, 1, 1 }).getDistanceSquared(Vector3d__<T>({ 2, 2, 2 }))));
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely( 3, Vector3d__<T>({ 2, 2, 2 }).getDistanceSquared(Vector3d__<T>({ 1, 1, 1 }))));


	//EXPECT_TRUE(expected, v1.getDistance(v0));
}


TYPED_TEST(VectorTest, TestGetDistance)
{
	using T = TypeParam;

	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(std::sqrt(T(2)), Vector2d<T>({ 1, 1 }).getDistance(Vector2d < T >({2, 2})) ) );
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(std::sqrt(T(2)), Vector2d<T>({ 2, 2 }).getDistance(Vector2d<T>({ 1, 1 }))));

	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(std::sqrt(T(3)), Vector3d__<T>({ 1, 1, 1 }).getDistance(Vector3d__<T>({ 2, 2, 2 }))));
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(std::sqrt(T(3)), Vector3d__<T>({ 2, 2, 2 }).getDistance(Vector3d__<T>({ 1, 1, 1 }))));


	//EXPECT_TRUE(expected, v1.getDistance(v0));
}

TYPED_TEST(VectorTest, TestGetInnerProduct)
{
	using T = TypeParam;

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( 4, Vector2d<T>({ 1, 1 }).getInnerProduct(Vector2d < T >({ 2, 2 }))));
}

