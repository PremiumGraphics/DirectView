#include "gtest/gtest.h"

#include "Bone.h"

using namespace Crystal::Math;
using namespace Crystal::Actor;

TEST(BoneTest, Test)
{
	const auto j1 = std::make_shared< Joint<float> >(Vector3d<float>(0, 0, 0));
	const auto j2 = std::make_shared< Joint<float> >(Vector3d<float>(1, 1, 1));

	const Bone<float> bone(j1, j2);
}