#include "gtest/gtest.h"

#include "RenderingBuffer.h"

#include "../Graphics/Surface.h"

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
	SurfaceSPtr<float> polygon = std::make_shared<Surface<float> >();
	polygon->add(Triangle<float>(), ColorRGBA<float>());
	PolygonObjectSPtr<float> pid = std::make_shared<PolygonObject<float> >(polygon, 0);
	command.build({ pid });
	EXPECT_EQ(18, command.getPositions().size());
}

TEST(PointRenderingCommandTest, TestBuildScalarSpace)
{
	Volume3d<float> ss;
	PointRenderingBuffer<float> command;
	command.build(ss,0);
	EXPECT_EQ(3, command.getPoints().size());
	EXPECT_EQ(1, command.getIds().size());
}