#include "gtest/gtest.h"

#include "PolygonFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

TEST(PolygonFactoryTest, TestCreate)
{
	PolygonFactory<float> factory;
	//ScalarSpace3d<float> ss;

	const auto& p = factory.create(ScalarSpace3d<float>());
	EXPECT_EQ(0, p.getId());

	const auto& p2 = factory.create(ScalarSpace3d<float>());
	EXPECT_EQ(1, p2.getId());

}

