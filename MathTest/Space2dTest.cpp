#include "gtest/gtest.h"

#include "../Math/Space2d.h"

using namespace Crystal::Math;

TEST(Space2dTest, TestGetSize)
{
	EXPECT_EQ(Vector2d<float>(1.0f, 1.0f), Space2d(1,1).getSizes());
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

TEST(Space2dTest, TestToQuads)
{
	{		
		const std::vector<Quad>& quads = Space2d(2, 2).toQuads( Bitmap2x2() );
		EXPECT_TRUE(quads.empty());
	}

	{
		Bitmap2d<2, 2> bmp;
		bmp.set(0, 0);
		Space2d space(2, 2);
		const std::vector<Quad>& quads = space.toQuads(bmp);
		EXPECT_EQ(1, quads.size());
		EXPECT_EQ(Vector2d<float>(0.5f, 0.5f), quads.front().getCenter());
	}
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