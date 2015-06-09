#include "gtest/gtest.h"

#include "LightFactory.h"

using namespace Crystal::Command;
using namespace Crystal::Graphics;


TEST(LightFactoryTest, TestBuild)
{
	LightFactory factory;
	factory.build();
	EXPECT_EQ(1, factory.getLights().size());
}

TEST(LightBuilderTest, TestRemove)
{
	LightFactory factory;
	factory.build();
	LightSPtr l = factory.build();
	factory.remove(l);
	EXPECT_EQ(1, factory.getLights().size());
}