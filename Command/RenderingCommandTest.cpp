#include "gtest/gtest.h"

#include "RenderingCommand.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

TEST(RenderingCommandTest, TestClear)
{
	WireFrameRenderingBuffer<float> command;
	command.clear();
}

TEST(RenderingCommandTest, TestBuildPolygon)
{
	WireFrameRenderingBuffer<float> command;
	PolygonSPtr<float> polygon = std::make_shared<Polygon<float> >();
	polygon->add(Triangle<float>(), ColorRGBA<float>());
	command.build({ polygon });
	EXPECT_EQ(18, command.getPositions().size());
}

TEST(PointRenderingCommandTest, TestBuildScalarSpace)
{
	ScalarSpace3d<float> ss;
	PointRenderingBuffer<float> command;
	command.build(ss,0);
	EXPECT_EQ(3, command.getPoints().size());
	EXPECT_EQ(1, command.getIds().size());
}