#include "gtest/gtest.h"

#include "../Command/MainFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(MainFactoryTest, TestFind)
{
	Model<float> factory;
	factory.find(0);
}
