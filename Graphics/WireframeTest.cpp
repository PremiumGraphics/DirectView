#include "gtest/gtest.h"

#include "Wireframe.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(WireframeTest, TestTriangle)
{
	Triangle < float > t;
	Wireframe<float> wf;
	wf.add(t);
	EXPECT_EQ(3, wf.getLines().size());
}