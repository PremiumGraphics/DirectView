#include "gtest/gtest.h"

#include "../Math/Space1d.h"

using namespace Crystal::Math;

using Space1df = Space1d<1,float>;
using Space1df2 = Space1d<2, float>;


TEST(Space1dTest, TestGetStart)
{
	EXPECT_EQ(Position1d<float>({ 0.0 }), Space1df().getStart());
	EXPECT_EQ(Position1d<float>({ 1.0 }), Space1df(Position1d<float>({ 1.0f }), Vector1d<float>({ 2 }) ).getStart());
}

TEST(Space1dTest, TestGetEnd)
{
	EXPECT_EQ(1.0f, Space1df().getEnd());
	EXPECT_EQ(3.0f, Space1df(Position1d<float>({ 1.0f }), Vector1d < float >({2})).getEnd() );
}

TEST(Space1dTest, TestGetLength)
{
	EXPECT_EQ(Vector1d<float>({ 1 }), Space1df().getLength());
	EXPECT_EQ( Vector1d < float >({2}), Space1df( Position1d<float>({ 1.0f }), Vector1d < float >({ 2 })).getLength() );
}

/*
TEST(Space1dTest, TestGetBoundingLine)
{
	EXPECT_EQ(Line1d<float>(Position1d<float>({ 0.0f }), 1.0f), Space1df().getBoundingLine());
}
*/

TEST(Space1dTest, TestGetSize)
{
	EXPECT_EQ(1.0f, Space1df().getSize());
	//EXPECT_EQ(2.0f, Space1d<1>(1.0f, 2.0f).getLength());
}


TEST(Space1dTest, TestToPoints)
{
	EXPECT_TRUE( Space1df2(Bitmap2("00")).toPositions().empty());

	{
		const Position1dVector<float> expected = { Position1d<float>({ 0.25f }) };
		const auto actual = Space1df2(Bitmap1d<2>("01")).toPositions();
		EXPECT_EQ(expected, actual);
	}
	{
		const Position1dVector<float> expected = { Position1d<float>({ 0.75f }) };
		const auto actual = Space1df2(Bitmap1d<2>("10")).toPositions();
		EXPECT_EQ( expected, actual );

	}
	{
		const Position1dVector<float> expected = { Position1d < float > { {0.25f } }, Position1d < float > {{0.75f} } };
		const auto actual = Space1df2(Bitmap1d<2>("11")).toPositions();
		EXPECT_EQ( expected, actual );
	}
}

TEST(Space1dTest, TestToBoundaryPositions)
{
	EXPECT_TRUE(Space1df2(Bitmap2("00")).toBoundaryPositions().empty());
	EXPECT_TRUE(Space1df2(Bitmap2("11")).toBoundaryPositions().empty());

	{
		const Position1dVector<float> expected = { Position1d<float>({ 0.5f }) };

		EXPECT_EQ(expected, Space1df2(Bitmap2("01")).toBoundaryPositions() );
		EXPECT_EQ(expected, Space1df2(Bitmap2("10")).toBoundaryPositions() );
	}
}

TEST(Space1dTest, TestGetTotalLength)
{
	EXPECT_EQ(0.0f, Space1df2(Bitmap1d<2>("00")).getTotalLength());
	EXPECT_EQ(1.0f, Space1df2(Bitmap1d<2>("01")).getTotalLength());
	EXPECT_EQ(1.0f, Space1df2(Bitmap1d<2>("10")).getTotalLength());
	EXPECT_EQ(2.0f, Space1df2(Bitmap1d<2>("11")).getTotalLength());
}