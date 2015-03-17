#include "gtest/gtest.h"

#include "../Graphics/Light.h"

using namespace Crystal::Graphics;

TEST(LightTest, TestConstruct )
{
	Light l;
	EXPECT_EQ( ColorRGB<float>::Blue(), l.getAmbient() );
}

TEST(LightBuilderTest, TestBuild)
{
	LightBuilder builder;
	builder.build();
	EXPECT_EQ(1, builder.getLights().size());
}