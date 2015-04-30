#include "gtest/gtest.h"

#include "../Math/IntersectionFindAlgo.h"

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST(IntersectionFindAlgoTest, TestHasIntersectionScanLineX)
{
	{
		ScanLineX sline(0.0, 0.0);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		EXPECT_TRUE(sline.hasIntersections(b));
	}

	{
		ScanLineX sline(1.0, 0.5);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		EXPECT_FALSE(sline.hasIntersections(b));
	}
}

TEST(IntersectionFindAlgoTest, TestGetIntersectionsScanLineX)
{
	{
		ScanLineX sline(0.0, 0.0);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		const auto actual = sline.getIntersections(b);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Vector3d(-0.5, 0.0, 0.0), actual[0]);
		EXPECT_EQ(Vector3d(0.5, 0.0, 0.0), actual[1]);
	}

	{
		ScanLineX sline(0.0, 0.0);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(1.5, 0.5, 0.5));
		const auto actual = sline.getIntersections(b);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Vector3d(-0.5, 0.0, 0.0), actual[0]);
		EXPECT_EQ(Vector3d(1.5, 0.0, 0.0), actual[1]);
	}


	{
		ScanLineX sline(1.0, 0.5);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		EXPECT_TRUE( sline.getIntersections(b).empty() );
	}
}

TEST(IntersectionFindAlgoTest, TestHasIntersectionScanLineY)
{
	{
		ScanLineY sline(0.0, 0.0);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		EXPECT_TRUE(sline.hasIntersections(b));
	}

	{
		ScanLineY sline(1.0, 0.5);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		EXPECT_FALSE(sline.hasIntersections(b));
	}
}

TEST(IntersectionFindAlgoTest, TestGetIntersectionsScanLineY)
{
	{
		ScanLineY sline(0.0, 0.0);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		const auto actual = sline.getIntersections(b);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Vector3d(0.0, -0.5, 0.0), actual[0]);
		EXPECT_EQ(Vector3d(0.0, 0.5, 0.0), actual[1]);
	}

	{
		ScanLineY sline(1.0, 0.5);
		Box b(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5));
		EXPECT_TRUE(sline.getIntersections(b).empty());
	}
}

TEST(InterSectionFindAlgoTest, TestGetIntersections)
{
	ScanLineX sline(0.0, 0.0);
	std::vector<Box> boxes{
		Box(Vector3d(-0.5, -0.5, -0.5), Vector3d(0.5, 0.5, 0.5)),
		Box(Vector3d(0.5, -0.5, -0.5), Vector3d(1.5, 0.5, 0.5))
	};

	IntersectionFindAlgo algo;
	const auto& actual = algo.getIntersections(sline, boxes);
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(Vector3d(-0.5, 0.0, 0.0), actual[0]);
	EXPECT_EQ(Vector3d(1.5, 0.0, 0.0), actual[1]);
}