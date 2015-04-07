#include "gtest/gtest.h"

#include "BazierCurve.h"

using namespace Crystal::Math;

TEST(BazierCurveTest, TestBinomialCoefficient)
{
	BernsteinBasicFunc bb;
	const float coe = bb.getBinomialCoefficient(1, 1);
	EXPECT_FLOAT_EQ(1.0f, coe);
}

TEST(BazierCurveTest, Test)
{
	BernsteinBasicFunc bb;
	const float actual = bb.get(1, 1, 1.0f);
	EXPECT_FLOAT_EQ(1.0f, actual);
}