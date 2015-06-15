#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"
#include "ScalarSpaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(ScalarSpaceFactoryTest, TestCreate)
{
	ScalarSpaceFactory<float> factory;
	const GridConfig<float> config(5, 5, 5, Space3d<float>( Vector3d<float>(0,0,0), Vector3d<float>(1,1,1) ) );
	const auto& ss = factory.create(config);
	EXPECT_EQ(0, ss->getId());
}