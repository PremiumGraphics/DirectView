#include "gtest/gtest.h"

#include "SurfaceModel.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

TEST(SurfaceModelTest, TestCreate)
{
	SurfaceModel<float> factory;
	//ScalarSpace3d<float> ss;

	const auto& p = factory.create(Volume3d<float>());
	EXPECT_EQ(0, p->getId());

	const auto& p2 = factory.create(Volume3d<float>());
	EXPECT_EQ(1, p2->getId());

	EXPECT_EQ( p2, factory.find(1) );
	EXPECT_EQ( nullptr, factory.find(2) );
}