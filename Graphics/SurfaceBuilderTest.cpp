#include <gtest/gtest.h>

#include "SurfaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(SurfaceBuilderTest, TestImage)
{
	SurfaceBuilder builder;
	ImageRGBA<float> image(2, 2);
	image.setColor(0, 0, ColorRGBA<float>(0.0, 0.0, 0.0, 1.0f));
	image.setColor(1, 1, ColorRGBA<float>(0.0, 0.0, 0.0, 1.0f));
	const Vector3dVector& edges = builder.findEdges(image);
	EXPECT_EQ(2, edges.size());
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), edges.front());
	EXPECT_EQ(Vector3d(1.0f, 1.0f, 0.0f), edges.back());
}