#include "gtest/gtest.h"

#include "../Math/Space1d.h"

using namespace Crystal::Math;

TEST( Space1dTest, TestConstruct )
{
	Space1d space;
	EXPECT_EQ(0.0f, space.getStart());
	EXPECT_EQ(1.0f, space.getEnd());
	EXPECT_EQ(1.0f, space.getLength());
}

TEST(Space1dTest, TestToPoints)
{
	EXPECT_TRUE( Space1d().toPositions(Bitmap1d<2>("00")).empty());
	EXPECT_EQ(std::vector < float > {0.5f}, Space1d().toPositions(Bitmap1d<2>("01")));
	EXPECT_EQ(std::vector < float > {1.5f}, Space1d().toPositions(Bitmap1d<2>("10")));

	{
		const std::vector<float> expected = { 0.5f, 1.5f };
		const std::vector<float> actual = Space1d().toPositions(Bitmap1d<2>("11"));
		EXPECT_EQ( expected, actual );
	}
}