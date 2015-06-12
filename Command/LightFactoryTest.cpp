#include "gtest/gtest.h"

#include "LightFactory.h"

using namespace Crystal::Command;
using namespace Crystal::Graphics;


TEST(LightFactoryTest, TestBuild)
{
	LightFactory<float> factory;
	factory.build();
	EXPECT_EQ(1, factory.getLights().size());
}

TEST(LightBuilderTest, TestRemove)
{
	LightFactory<float> factory;
	factory.build();
	LightSPtr<float> l = factory.build();
	factory.remove(l);
	EXPECT_EQ(1, factory.getLights().size());
}