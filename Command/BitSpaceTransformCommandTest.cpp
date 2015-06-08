#include "gtest/gtest.h"

#include "BitSpaceTransformCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(BitSpaceTransformCommandTest, TestNot)
{
	BitSpaceTransformCommand command;
	const BitSpace3dSPtr<float>& space = std::make_shared<BitSpace3d<float> >();
	command.add(space);
	command.not();
}

TEST(BitSpaceTransformCommandTest, TestScale)
{
	BitSpaceTransformCommand command;
	command.scale(Vector3d<float>(1, 2, 3));
}