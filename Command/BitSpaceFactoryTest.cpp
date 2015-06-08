#include "gtest/gtest.h"

#include "BitSpaceFactory.h"

using namespace Crystal::Command;

TEST(BitSpaceFactoryTest, TestAddBitSpace)
{
	BitSpaceFactory sf;
	const auto b1 = sf.createBox(5, 5, 5);
	EXPECT_EQ( 0, sf.getId(b1) );
	const auto b2 = sf.createBox(5, 5, 5);
	EXPECT_EQ( 1, sf.getId(b2) );
}