#include "gtest/gtest.h"

#include "../Math/Kernel.h"

using namespace Crystal::Math;

TEST(Kernel1dTest, Test)
{
	Gaussian1d<float> k;
	const auto expected = 1.0 / std::sqrt(2.0 * Tolerance<float>::getPI());
	EXPECT_FLOAT_EQ(expected, k.get(0));
}