#include "gtest/gtest.h"

#include "../Math/Space2d.h"

using namespace Crystal::Math;

TEST(Space2dTest, TestGetSize)
{
	EXPECT_EQ( Vector2d<float>(1.0f, 1.0f), Space1x1().getSizes());
}

TEST(Space2dTest, TestEquals)
{
	EXPECT_EQ(Space1x1(), Space1x1());
	EXPECT_NE(Space1x1(Position2d<float>(1.0f, 1.0f)), Space1x1());
}

TEST(Space2dTest, TestGetResX)
{
	EXPECT_EQ(2, Space2x2().getResX());
	EXPECT_EQ(4, Space4x2().getResX());

//	EXPECT_EQ(20, s.getResY());
}

TEST(Space2dTest, TestGetStart)
{
	const Space2d<10, 20> s(Position2d<float>(1.0f, 2.0f) );
	EXPECT_EQ(Position2d<float>(1.0f, 2.0f), s.getStart());
	EXPECT_EQ(Position2d<float>(0.0f, 0.0f), Space2x2().getStart());
}

TEST(Space2dTest, TestGetEnd)
{
	const Space2d<10, 20> s(Position2d<float>(1.0f, 2.0f) );
	EXPECT_EQ(Position2d<float>(2.0f, 3.0f), s.getEnd());
}

/*
TEST(Space2dTest, TestMove)
{
	Space2x2 s(Vector2d<float>(1.0f, 2.0f));
	 //s.move(Vector2d<float>(10.0f, 10.0f));

}
*/

/*
TEST(Space2dTest, TestGetBoundingQuad)
{
	const Space2d<2, 2> s(Vector2d<float>(1.0f, 2.0f) );
	const Quad expected( Vector2d<float>(11.0f, 22.0f), Position2d<float>(1.0f, 2.0f) );
	const auto& actual = s.getBoundingQuad();
	EXPECT_EQ(expected, actual);
}
*/

TEST(Space2dTest, TestToBoundaryPositions)
{
	EXPECT_TRUE(Space2x2().toBoundaryPositions(Bitmap2x2()).empty());

	/*
	{
		const auto actual = Space2x2().toBoundaryPositions(Bitmap2x2("0001"));
		const Position2dVector < float > expected{
			Position2d<float>(0.5, 0.0),
			Position2d<float>(0.0, 0.5)
		};
		EXPECT_EQ(expected, actual);
	}
	*/
}

TEST(Space2dTest, TestToQuads)
{
	{		
		const std::vector<Quad<float> >& quads = Space2d<2, 2>().toQuads(Bitmap2x2());
		EXPECT_TRUE(quads.empty());
	}

	{
		Bitmap2d<2, 2> bmp;
		bmp.set(0, 0);
		Space2d<2, 2> space;
		const std::vector<Quad<float> >& quads = space.toQuads(bmp);
		EXPECT_EQ(1, quads.size());
		EXPECT_EQ(Position2d<float>(0.5f, 0.5f), quads.front().getCenter());
	}
}

TEST(Space2dTest, TestHasIntersection)
{
	Space2d<2, 2> space1;
	Space2d<2, 2> space2;
	EXPECT_TRUE( space1.hasIntersection(space2) );
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