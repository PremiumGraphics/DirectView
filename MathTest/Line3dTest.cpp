#include "gtest/gtest.h"

#include "../Math/Line3d.h"

using namespace Crystal::Math;

TEST(LineTest, TestConstruct)
{
	Line3d<float> line;
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), line.getStart());
	EXPECT_EQ(Vector3d(1.0f, 0.0f, 0.0f), line.getEnd());
}

TEST(LineTest, TestGetDistance)
{
	EXPECT_FLOAT_EQ(1.0f, Line3d<float>().getLength());
}