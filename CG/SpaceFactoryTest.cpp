#include "gtest/gtest.h"

#include "SpaceFactory.h"

using namespace Crystal::CGS;

TEST(SpaceFactoryTest, TestAddBitSpace)
{
	SpaceFactory sf;
	const auto actual = sf.createBox(5, 5, 5);
	EXPECT_EQ( 0, sf.getId(actual) );
}