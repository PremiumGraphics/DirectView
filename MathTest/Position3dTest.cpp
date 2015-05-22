#include "gtest/gtest.h"

#include "../Math/Position3d.h"

template<class T>
class Position3dTest : public testing::Test {
};

typedef ::testing::Types<float> TestTypes;

TYPED_TEST_CASE(Position3dTest, TestTypes);

using namespace Crystal::Math;

TYPED_TEST(Position3dTest, TestGetX)
{
	using T = TypeParam;
	EXPECT_EQ(0.0f, Position3d<T>().getX());
	EXPECT_EQ(1.0f, Position3d<T>(1.0f, 2.0f, 3.0f).getX());
}

TYPED_TEST(Position3dTest, TestGetY)
{
	using T = TypeParam;
	EXPECT_EQ(0.0f, Position3d<T>().getY());
	EXPECT_EQ(2.0f, Position3d<T>(1.0f, 2.0f, 3.0).getY());
}

TYPED_TEST(Position3dTest, TestGetZ)
{
	using T = TypeParam;
	EXPECT_EQ(0.0f, Position3d<T>().getZ());
	EXPECT_EQ(3.0f, Position3d<T>(1.0f, 2.0f, 3.0).getZ());
}

TYPED_TEST(Position3dTest, TestGetDistance)
{
	using T = TypeParam;
	EXPECT_EQ(0.0f, Position3d<T>().getDistance(Position3d<T>()));
	EXPECT_FLOAT_EQ( std::sqrt( 3.0f ), Position3d<T>().getDistance(Position3d<T>(1.0, 1.0, 1.0)));
}

TYPED_TEST(Position3dTest, TestGetDistanceSquared)
{
	using T = TypeParam;
	EXPECT_EQ(0.0f, Position3d<T>().getDistanceSquared(Position3d<T>()));
	EXPECT_FLOAT_EQ(3.0f, Position3d<T>().getDistanceSquared(Position3d<T>(1.0, 1.0, 1.0)));

}

TYPED_TEST(Position3dTest, TestDiff)
{
	using T = TypeParam;

	EXPECT_EQ(Vector3d_<T>(1.0, 0.0, 0.0), Position3d<T>(0.0, 0.0, 0.0).diff(Position3d<T>(1.0, 0.0, 0.0)) );
	EXPECT_EQ(Vector3d_<T>(-1.0, 0.0, 0.0), Position3d<T>(2.0, 0.0, 0.0).diff(Position3d<T>(1.0, 0.0, 0.0)));

}

TYPED_TEST(Position3dTest, TestAdd)
{
	using T = TypeParam;
	EXPECT_EQ( Position3d<T>(3.0, 0.0, 0.0), Position3d<T>(1.0, 0.0, 0.0)+ Vector3d_<T>(2.0, 0.0, 0.0) );

}