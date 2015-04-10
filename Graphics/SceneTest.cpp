#include "gtest/gtest.h"

#include "Scene.h"

using namespace Crystal::Graphics;

TEST(SceneTest, TestConstruct)
{
	Scene scene;
	EXPECT_EQ(nullptr, scene.getChild());
	EXPECT_EQ(nullptr, scene.getParent());
}