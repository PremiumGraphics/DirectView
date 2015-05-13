#include "gtest/gtest.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

TEST(ToleranceTest, TestGetLooseTolerance)
{
	EXPECT_EQ( 1.0e-09f, Tolerance<float>::getLooseTolerance());
	EXPECT_EQ( 1.0e-18f, Tolerance<float>::getStrictTolerance());

	EXPECT_EQ( 1.0e-09, Tolerance<double>::getLooseTolerance());
	EXPECT_EQ( 1.0e-18, Tolerance<double>::getStrictTolerance());

}
