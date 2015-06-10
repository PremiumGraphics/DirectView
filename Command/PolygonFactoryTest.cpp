#include "gtest/gtest.h"

#include "PolygonFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

TEST(PolygonFactoryTest, TestCreate)
{
	PolygonFactory<float> factory;
	ScalarSpace3d<float> ss;

	const auto& p = factory.create(ss);
	EXPECT_TRUE(p != nullptr);
}

