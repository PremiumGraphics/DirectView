#include "gtest/gtest.h"

#include "RenderingCommand.h"

using namespace Crystal::CGS;

TEST(RenderingCommandTest, TestClear)
{
	RenderingCommand command;
	command.clear();
}