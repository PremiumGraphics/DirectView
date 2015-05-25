#include "gtest/gtest.h"

#include "../Math/Line2d.h"

using namespace Crystal::Math;

TEST(Line2dTest, TestGetStart)
{
	EXPECT_EQ(Position2d<float>({ 0.0f, 0.0f }), Line2d<float>().getStart());
	EXPECT_EQ(Position2d<float>({ 1.0f, 0.0f }), Line2d<float>(Position2d<float>({ 1.0f, 0.0f })).getStart());
}