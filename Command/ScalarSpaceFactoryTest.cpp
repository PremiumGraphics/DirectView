#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"
#include "ScalarSpaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(ScalarSpaceFactoryTest, TestCreateCone)
{
	ScalarSpaceFactory factory;
	EXPECT_EQ( -1, factory.getId(nullptr) );
	const auto& ss = factory.create(5, 5, 5);
	EXPECT_EQ(0, factory.getId(ss));
}