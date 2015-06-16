#include "gtest/gtest.h"

#include "LightModel.h"

using namespace Crystal::Command;
using namespace Crystal::Graphics;


TEST(LightFactoryTest, TestBuild)
{
	LightModel<float> factory;
	factory.build();
	EXPECT_EQ(1, factory.getLights().size());
}

TEST(LightBuilderTest, TestRemove)
{
	LightModel<float> factory;
	factory.build();
	LightSPtr<float> l = factory.build();
	factory.remove(l);
	EXPECT_EQ(1, factory.getLights().size());
}