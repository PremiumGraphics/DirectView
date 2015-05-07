#include "gtest/gtest.h"

#include "../Math/EdgeDetectionAlgo.h"

using namespace Crystal::Math;

TEST(EdgeDetectionAlgoTest, Test1d)
{
	EdgeDetectionAlgo algo;
	Bitmap1d<4> bmp("1110");
	Bitmap1d<4> actual = algo.detect(bmp);
	Bitmap1d<4> expected("0010");
	EXPECT_EQ( expected, actual );
}

TEST(EdgeDetectionAlgoTest, Test2d)
{
	EdgeDetectionAlgo algo;
	Bitmap2d<4, 4> bmp;
}