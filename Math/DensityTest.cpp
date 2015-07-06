#include "gtest/gtest.h"

#include "Density.h"

using namespace Crystal::Math;

TEST(DensityTest, TestAdd)
{
	Density<float> d;
	d.add(2.0);
	EXPECT_EQ(1.0, d.get());
}

TEST(DensityTest, TestSub)
{
	Density<float> d;
	d.sub(2.0);
	EXPECT_EQ(-1.0, d.get());
}