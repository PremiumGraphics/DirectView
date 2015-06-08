#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"
#include "ScalarSpaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(ScalarSpaceFactoryTest, TestGetId)
{
	ScalarSpaceFactory factory;
	EXPECT_EQ( -1, factory.getId(nullptr) );
}