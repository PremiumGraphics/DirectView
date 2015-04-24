#include "gtest/gtest.h"
#include "PhysicsModel.h"

using namespace Crystal::IO;

TEST(PhysicsModelTest, TestConstruct)
{
	PhysicsModel model;
	EXPECT_TRUE(model.getObjects().empty());
}