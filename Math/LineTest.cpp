#include "gtest/gtest.h"

#include "../Math/Line.h"

using namespace Crystal::Math;

TEST(LineTest, TestConstruct)
{
	Line line;
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), line.getStart());
	EXPECT_EQ(Vector3d(1.0f, 0.0f, 0.0f), line.getEnd());
}

TEST(LineTest, TestGetDistance)
{
	Line line;
	const float length = line.getLength();
	EXPECT_FLOAT_EQ(1.0f, length);
}