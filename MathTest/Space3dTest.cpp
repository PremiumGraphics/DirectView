#include "gtest/gtest.h"

#include "../Math/Space3d.h"

using namespace Crystal::Math;

TEST(Space3dTest, TestConstruct)
{
	Space3d<1,1,1> space;
	EXPECT_EQ(Vector3d(1.0f, 1.0f, 1.0f), space.getSizes());
	//space.setMinSize(1.0f);
	//space.
}

TEST(Space3dTest, TestConstructByOrigin)
{
	Space3d<10,20,30> s( Vector3d( 1.0f, 2.0f, 3.0f) );
	EXPECT_EQ( 10, s.getResX());
	EXPECT_EQ( 20, s.getResY());
	EXPECT_EQ( 30, s.getResZ());
}

TEST(Space3dTest, TestGetEnd)
{
	Space3d<10,20,30> s(Vector3d(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(Vector3d(11.0f, 22.0f, 33.0f), s.getEnd());
}

TEST(Space3dTest, TestGetHashedIndex)
{
	Space3d<1,1,1> space;

	const std::vector<int>& actual = space.getHashedIndex(Vector3d(1.5f, 0.0f, 0.0f));
	const std::vector<int> expected{ 1, 0, 0 };
	EXPECT_EQ(expected, actual);
}

TEST(Space3dTest, TestToBoxesEmpty)
{
	using Space2x2x2 = Space3d < 2, 2, 2 > ;
	EXPECT_TRUE( Space2x2x2().toBoxes(Bitmap2x2x2()).empty());

	{
		Bitmap3d<2, 2, 2> bmp;
		bmp.set(0, 0, 0);
		Space3d<2,2,2> space;
		const auto& boxes = space.toBoxes(bmp);
		EXPECT_EQ(1, boxes.size());
		EXPECT_EQ(Vector3d(0.5f, 0.5f, 0.5f), boxes.front().getCenter());
	}

	{
		Bitmap3d<2, 2, 2> bmp;
		bmp.set(0, 0, 0);
		bmp.set(1, 0, 0);
		Space3d<2,2,2> space;
		const auto& boxes = space.toBoxes(bmp);
		EXPECT_EQ(2, boxes.size());
		EXPECT_EQ(Vector3d(0.5f, 0.5f, 0.5f), boxes[0].getCenter());
		EXPECT_EQ(Vector3d(1.5f, 0.5f, 0.5f), boxes[1].getCenter());
	}
}