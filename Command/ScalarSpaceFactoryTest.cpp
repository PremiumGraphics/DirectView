#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"
#include "ScalarSpaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(ScalarSpaceFactoryTest, TestCreateCone)
{
	ScalarSpaceFactory factory;
	EXPECT_EQ( -1, factory.getId(nullptr) );
	const auto config = std::make_tuple(5, 5, 5, Space3d<float>( Vector3d<float>(0,0,0), Vector3d<float>(1,1,1) ) );
	const auto& ss = factory.create(config);
	EXPECT_EQ(0, factory.getId(ss));
}