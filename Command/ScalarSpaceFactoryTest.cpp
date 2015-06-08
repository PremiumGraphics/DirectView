#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"
#include "ScalarSpaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(ScalarSpaceFactoryTest, TestGetId)
{
	ScalarSpaceFactory factory;
	EXPECT_EQ( -1, factory.getId(nullptr) );
	ScalarSpace3dSPtr<float> ss = std::make_shared<ScalarSpace3d<float> >();
	factory.add(ss);
	EXPECT_EQ(0, factory.getId(ss));
}