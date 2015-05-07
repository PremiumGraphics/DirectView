#include "gtest/gtest.h"

#include "../Math/Quad.h"

#include "Bitmap3dConverter.h"

using namespace Crystal::Math;

TEST(BitmapConverterTest, TestToQuads)
{
	{
		Bitmap2d<2,2> bmp;
		BitmapConverter converter;
		const std::vector<Quad>& quads = converter.toQuads(bmp);
		EXPECT_TRUE(quads.empty());
	}

	{
		Bitmap2d<2, 2> bmp;
		bmp.set(0, 0);
		BitmapConverter converter;
		const std::vector<Quad>& quads = converter.toQuads(bmp);
		EXPECT_EQ(1, quads.size());
		EXPECT_EQ(Vector2d<float>(0.5f, 0.5f), quads.front().getCenter());
	}
}

TEST(BitmapConverterTest, TestToBoxesEmpty)
{
	{
		Bitmap3d<2,2,2> bmp;
		Space3d space(2,2,2);
		BitmapConverter converter;
		const auto& boxes = converter.toBoxes(bmp, space);
		EXPECT_TRUE(boxes.empty());
	}
}

TEST(BitmapConverterTest, TestToOneBox)
{
	Bitmap3d<2,2,2> bmp;
	bmp.set(0, 0, 0);
	Space3d space(2, 2, 2);
	BitmapConverter converter;
	const auto& boxes = converter.toBoxes(bmp, space);
	EXPECT_EQ( 1, boxes.size() );
	EXPECT_EQ(Vector3d(0.5f, 0.5f, 0.5f), boxes.front().getCenter());
}

TEST(BitmapConverterTest, TestToTwoBoxes)
{
	Bitmap3d<2,2,2> bmp;
	bmp.set(0, 0, 0);
	bmp.set(1, 0, 0);
	Space3d space(2, 2, 2);
	BitmapConverter converter;
	const auto& boxes = converter.toBoxes(bmp, space);
	EXPECT_EQ(2, boxes.size());
	EXPECT_EQ(Vector3d(0.5f, 0.5f, 0.5f), boxes[0].getCenter());
	EXPECT_EQ(Vector3d(1.5f, 0.5f, 0.5f), boxes[1].getCenter());
}