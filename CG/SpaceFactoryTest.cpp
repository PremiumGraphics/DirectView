#include "gtest/gtest.h"

#include "SpaceFactory.h"

using namespace Crystal::CGS;

TEST(SpaceFactoryTest, TestAddBitSpace)
{
	SpaceFactory sf;
	const auto b1 = sf.createBox(5, 5, 5);
	EXPECT_EQ( 0, sf.getId(b1) );
	const auto b2 = sf.createBox(5, 5, 5);
	EXPECT_EQ( 1, sf.getId(b2) );
}