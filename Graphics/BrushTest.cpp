#include "gtest/gtest.h"

#include "../Graphics/Brush.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(BrushTest, TestConstruct)
{
	BlendBrush<float> brush;
	EXPECT_EQ( Vector3d<float>(1,1,1), brush.getSize() );
}

TEST(BrushTest, TestMove)
{
	BlendBrush<float> brush( Vector3d<float>(1,2,3));
	brush.move(Vector3d <float>(3, 2, 1));
	EXPECT_EQ(Vector3d<float>(4, 4, 4), brush.getCenter());
}