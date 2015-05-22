#include "gtest/gtest.h"

#include "../Math/Triangle.h"

using namespace Crystal::Math;

TEST(TriangleTest, TestGet)
{
	EXPECT_EQ(Position3d<float>(0.0, 0.0, 0.0), Triangle<float>().getv0());
	EXPECT_EQ(Position3d<float>(1.0, 0.0, 0.0), Triangle<float>().getv1());
	EXPECT_EQ(Position3d<float>(0.0, 1.0, 0.0), Triangle<float>().getv2());
}

TEST(TriangleTest, TestIsCCW)
{
	EXPECT_TRUE( Triangle<float>().isCCW() );
}
