#include "gtest/gtest.h"

#include "Skeleton.h"

using namespace Crystal::Math;
using namespace Crystal::Actor;

TEST(SkeletonTest, TestBuild)
{
	using T = float;
	Skelton<T> actor;
	actor.buildBone(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	EXPECT_EQ(1, actor.getBones().size());
	EXPECT_EQ(2, actor.getJoints().size());
}