#include "gtest/gtest.h"

#include "../Command/MainModel.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(MainFactoryTest, TestFind)
{
	MainModel<float> factory;
	factory.find(0);
}
