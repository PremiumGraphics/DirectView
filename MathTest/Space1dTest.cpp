#include "gtest/gtest.h"

#include "../Math/Space1d.h"

using namespace Crystal::Math;

TEST(Space1dTest, TestGetStart)
{
	EXPECT_EQ(0.0f, Space1d<1>().getStart());
	EXPECT_EQ(1.0f, Space1d<1>(1.0f, 2.0f).getStart());
}

TEST(Space1dTest, TestGetEnd)
{
	EXPECT_EQ(1.0f, Space1d<1>().getEnd());
	EXPECT_EQ(3.0f, Space1d<1>(1.0f, 2.0f).getEnd());
}

TEST(Space1dTest, TestGetLength)
{
	EXPECT_EQ(1.0f, Space1d<1>().getLength());
	EXPECT_EQ(2.0f, Space1d<1>(1.0f, 2.0f).getLength());
}

TEST(Space1dTest, TestGetBoundingLine)
{
	EXPECT_EQ(Line1d<float>(0.0f, 1.0f), Space1d<1>().getBoundingLine());
}


TEST(Space1dTest, TestGetSize)
{
	EXPECT_EQ(1.0f, Space1d<1>().getSize());
	//EXPECT_EQ(2.0f, Space1d<1>(1.0f, 2.0f).getLength());
}


TEST(Space1dTest, TestToPoints)
{
	EXPECT_TRUE(Space1d<2>(Bitmap1d<2>("00")).toPositions().empty());
	EXPECT_EQ(std::vector < float > {0.25f}, Space1d<2>(Bitmap1d<2>("01")).toPositions());
	EXPECT_EQ(std::vector < float > {0.75f}, Space1d<2>(Bitmap1d<2>("10")).toPositions());

	{
		const std::vector<float> expected = { 0.25f, 0.75f };
		const std::vector<float> actual = Space1d<2>(Bitmap1d<2>("11")).toPositions();
		EXPECT_EQ( expected, actual );
	}
}

TEST(Space1dTest, TestGetTotalLength)
{
	EXPECT_EQ(0.0f, Space1d<2>(Bitmap1d<2>("00")).getTotalLength());
	EXPECT_EQ(1.0f, Space1d<2>(Bitmap1d<2>("01")).getTotalLength());
	EXPECT_EQ(1.0f, Space1d<2>(Bitmap1d<2>("10")).getTotalLength());
	EXPECT_EQ(2.0f, Space1d<2>(Bitmap1d<2>("11")).getTotalLength());
}