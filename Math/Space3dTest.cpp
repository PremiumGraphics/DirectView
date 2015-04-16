#include "gtest/gtest.h"

#include "Space3d.h"

using namespace Crystal::Math;

TEST(Space3dTest, TestConstruct)
{
	Space3d space( 1.0f );
	EXPECT_TRUE( 1.0f, space.getMinSize());
	//space.setMinSize(1.0f);
	//space.
}

TEST(Space3dTest, TestGetIndex)
{
	Space3d space(1.0f);
	EXPECT_EQ(1.0f, space.getMinSize());

	const std::vector<int>& actual = space.getHashedIndex(Vector3d(1.5f, 0.0f, 0.0f));
	const std::vector<int> expected{ 1, 0, 0 };
	EXPECT_EQ(expected, actual);
}