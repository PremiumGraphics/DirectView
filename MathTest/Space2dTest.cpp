#include "gtest/gtest.h"

#include "../Math/Space2d.h"

using namespace Crystal::Math;

TEST(Space2dTest, TestConstruct)
{
	const Space2d space(1, 1);
	EXPECT_EQ(Vector2d<float>(1.0f, 1.0f), space.getSizes());
}

TEST(Space2dTest, TestConstructByOrigin)
{
	const Space2d s(Vector2d<float>(1.0f, 2.0f), 10, 20);
	EXPECT_EQ(10, s.getResX());
	EXPECT_EQ(20, s.getResY());
}

TEST(Space2dTest, TestGetStart)
{
	const Space2d s(Vector2d<float>(1.0f, 2.0f), 10, 20);
	EXPECT_EQ(Vector2d<float>(1.0f, 2.0f), s.getStart());
}

TEST(Space2dTest, TestGetEnd)
{
	const Space2d s(Vector2d<float>(1.0f, 2.0f), 10, 20);
	EXPECT_EQ(Vector2d<float>(11.0f, 22.0f), s.getEnd());
}

TEST(Space2dTest, TestGetBoundingQuad)
{
	const Space2d s(Vector2d<float>(1.0f, 2.0f), 10, 20);
	const Quad expected(Vector2d<float>(1.0f, 2.0f), Vector2d<float>(11.0f, 22.0f));
	const auto& actual = s.getBoundingQuad();
	EXPECT_EQ(expected, actual);
}

/*
TEST(Space3dTest, TestGetHashedIndex)
{
Space3d space(1, 1, 1);

const std::vector<int>& actual = space.getHashedIndex(Vector3d(1.5f, 0.0f, 0.0f));
const std::vector<int> expected{ 1, 0, 0 };
EXPECT_EQ(expected, actual);
}
*/