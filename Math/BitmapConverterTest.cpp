#include "gtest/gtest.h"

#include "../Math/Quad.h"

#include "Bitmap3dConverter.h"

using namespace Crystal::Math;

TEST(BitmapConverterTest, TestToQuads)
{
	{
		Bitmap2d<2> bmp(2);
		Bitmap3dConverter converter;
		const std::vector<Quad>& quads = converter.toQuads(bmp);
		EXPECT_TRUE(quads.empty());
	}

	{
		Bitmap2d<2> bmp(2);
		bmp.set(0, 0);
		Bitmap3dConverter converter;
		const std::vector<Quad>& quads = converter.toQuads(bmp);
		EXPECT_EQ(1, quads.size());
		EXPECT_EQ(Vector2d<float>(0.5f, 0.5f), quads.front().getCenter());
	}
}

TEST(BitmapConverterTest, TestToBoxes)
{
	{
		Bitmap3d<2> bmp(2,2);
		Bitmap3dConverter converter;
		const auto& boxes = converter.toBoxes(bmp);
		EXPECT_TRUE(boxes.empty());
	}
}