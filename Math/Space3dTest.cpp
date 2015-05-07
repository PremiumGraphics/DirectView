#include "gtest/gtest.h"

#include "Space3d.h"

using namespace Crystal::Math;

TEST(Space3dTest, TestConstruct)
{
	Space3d space( 1.0f );
	EXPECT_FLOAT_EQ( 1.0f, space.getMinSize());
	//space.setMinSize(1.0f);
	//space.
}

TEST(Space3dTest, TestConstructByOrigin)
{
	Space3d s( Vector3d( 1.0f, 2.0f, 3.0f), 10, 20, 30 );
	EXPECT_EQ( 10, s.getResX());
	EXPECT_EQ( 20, s.getResY());
	EXPECT_EQ( 30, s.getResZ());
}

TEST(Space3dTest, TestGetEnd)
{
	Space3d s(Vector3d(1.0f, 2.0f, 3.0f), 10, 20, 30);
	EXPECT_EQ(Vector3d(11.0f, 22.0f, 33.0f), s.getEnd());
}

TEST(Space3dTest, TestGetHashedIndex)
{
	Space3d space(1.0f);
	EXPECT_EQ(1.0f, space.getMinSize());

	const std::vector<int>& actual = space.getHashedIndex(Vector3d(1.5f, 0.0f, 0.0f));
	const std::vector<int> expected{ 1, 0, 0 };
	EXPECT_EQ(expected, actual);
}