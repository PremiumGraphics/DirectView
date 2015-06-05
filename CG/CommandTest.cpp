#include "gtest/gtest.h"

#include "Command.h"

using namespace Crystal::Math;
using namespace Crystal::CG;

TEST(CommandTest, TestCreateBox)
{
	Model m;
	Command command(&m);
	command.createBox(5,5,5);
	EXPECT_EQ(1, m.getBitSpaces().size());
}

TEST(CommandTest, TestCreateSphere)
{
	Model m;
	Command command(&m);
	command.createSphere(5, 5, 5);
	EXPECT_EQ(1, m.getBitSpaces().size());
}