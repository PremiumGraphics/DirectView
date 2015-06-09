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
