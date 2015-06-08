#include "gtest/gtest.h"

#include "Command.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(CommandTest, TestCreateBox)
{
	Model m;
	MainCommand command(&m);
	command.createBox(5,5,5);
	EXPECT_EQ(1, m.getBitSpaceFactory()->getBitSpaces().size());
}

TEST(CommandTest, TestCreateSphere)
{
	Model m;
	MainCommand command(&m);
	command.createSphere(5, 5, 5);
	EXPECT_EQ(1, m.getBitSpaceFactory()->getBitSpaces().size());
}