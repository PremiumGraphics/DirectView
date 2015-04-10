#include "gtest/gtest.h"

#include "../Graphics/Light.h"

using namespace Crystal::Graphics;

TEST(AmbientLightTest, TestConstruct )
{
	AmbientLight l;
	EXPECT_EQ( ColorRGB<float>::White(), l.getColor() );
}

TEST(DirectionalLightTest, TestConstruct)
{
	DirectionalLight l;
	EXPECT_EQ(ColorRGB<float>::White(), l.getColor());
}

TEST(LightBuilderTest, TestBuild)
{
	LightBuilder builder;
	builder.build();
	EXPECT_EQ(1, builder.getLights().size());
}

TEST(LightBuilderTest, TestRemove)
{
	LightBuilder builder;
	builder.build();
	LightSPtr l = builder.build();
	builder.remove(l);
	EXPECT_EQ(1, builder.getLights().size());
}

TEST(LightBuilderTest, TestClear)
{
	LightBuilder builder;
	builder.build();
	LightSPtr l = builder.build();
	builder.clear();
	EXPECT_TRUE( builder.getLights().empty() );

}