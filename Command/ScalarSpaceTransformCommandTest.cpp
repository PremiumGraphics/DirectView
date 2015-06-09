#include "gtest/gtest.h"

#include "ScalarSpaceTransformCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(ScalarSpaceTransformCommandTest, TestAdd)
{
	using T = float;
	ScalarSpaceTransformCommand<T> command;
	const auto ss = std::make_shared< ScalarSpace3d<T> >();
	EXPECT_EQ( 1, command.add(ss).getSpaces().size() );
}