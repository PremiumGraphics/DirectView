#include "gtest/gtest.h"

#include "../Math/ScanLineX.h"

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST(IntersectionFindAlgoTest, TestHasIntersection)
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