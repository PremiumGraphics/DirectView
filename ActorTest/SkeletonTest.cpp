#include "gtest/gtest.h"

#include "Skeleton.h"

using namespace Crystal::Math;
using namespace Crystal::Actor;

TEST(SkeletonTest, TestBuild)
{
	using T = float;
	Skeleton<T> actor;
	actor.buildBone(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	EXPECT_EQ(1, actor.getBones().size());
	EXPECT_EQ(2, actor.getJoints().size());
}

TEST(SkeletonTest, TestToLines)
{
	using T = float;
	Skeleton<T> actor;
	actor.buildBone(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const auto& actual = actor.toLines();

	Line3dVector<T> expected{
		Line3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1))
	};
	EXPECT_EQ(expected, actual);
}

TEST(SkeletonTest, TestBuildHand)
{
	using T = float;
	Skeleton<T> skeleton;

	const auto& root = skeleton.buildJoint(Vector3d<T>(0, 0, 0));
	const auto& first = skeleton.buildJoint(Vector3d<T>(-2, 1, 0));
	const auto& second = skeleton.buildJoint(Vector3d<T>(-1, 2, 0));
	const auto& middle = skeleton.buildJoint(Vector3d<T>(0, 2, 0));
	const auto& third = skeleton.buildJoint(Vector3d<T>(1, 2, 0));
	const auto& forth = skeleton.buildJoint(Vector3d<T>(2, 2, 0));

	skeleton.buildBone(root, first);
	skeleton.buildBone(root, second);
	skeleton.buildBone(root, middle);
	skeleton.buildBone(root, third);
	skeleton.buildBone(root, forth);

	EXPECT_EQ(6, skeleton.getJoints().size());
	EXPECT_EQ(5, skeleton.getBones().size());
	//skeleton.buildJoints()
}