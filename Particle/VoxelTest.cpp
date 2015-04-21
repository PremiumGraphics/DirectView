#include "gtest/gtest.h"

#include "../Math/Voxel.h"

using namespace Crystal::Math;

TEST(VoxelTest, TestConstruct)
{
	Box b;
	Voxel v(b);
	EXPECT_EQ(nullptr, v.getParent());
	EXPECT_TRUE(v.getChildren().empty());
}

TEST(VoxelTest, TestCreateChildren)
{
	Box b;
	Voxel v(b);
	v.createChildren();
	EXPECT_EQ(8, v.getChildren().size());
}