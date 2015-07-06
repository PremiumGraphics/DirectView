#include "gtest/gtest.h"

#include "Bone.h"

using namespace Crystal::Math;
using namespace Crystal::Actor;

TEST(BoneTest, Test)
{
	Bone<float> bone(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));
}