#include "gtest/gtest.h"

#include "MetaballFactory.h"

using namespace Crystal::Command;

TEST(MetaballFactoryTest, TestCreate)
{
	MetaballFactory<float> factory;

	const auto actual = factory.create(MetaballConfig<float>());
	EXPECT_EQ(0, actual.getId());
	EXPECT_EQ(1, factory.getBalls().size());

	const auto ball2 = factory.create(MetaballConfig<float>());
	EXPECT_EQ(1, ball2.getId());
	EXPECT_EQ(2, factory.getBalls().size());

	factory.clear();
	EXPECT_TRUE( factory.getBalls().empty() );

	EXPECT_EQ(0, factory.getNextId());
	//factory.add()
}