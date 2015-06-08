#include "gtest/gtest.h"

#include "RenderingCommand.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

TEST(RenderingCommandTest, TestClear)
{
	RenderingCommand command;
	command.clear();
}

TEST(RenderingCommandTest, TestBuildPolygon)
{
	RenderingCommand command;
	PolygonSPtr polygon = std::make_shared<Polygon>();
	polygon->add(Triangle<float>(), ColorRGBA<float>());
	command.build({ polygon });
	EXPECT_EQ(9, command.getPositions().size());
}

TEST(RenderingCommandTest, TestBuildScalarSpace)
{
	ScalarSpace3d<float> ss;
	RenderingCommand command;
	command.build(ss,0);
	EXPECT_EQ(3, command.points.size());
	EXPECT_EQ(1, command.ids.size());
}