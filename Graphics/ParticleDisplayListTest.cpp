#include "gtest/gtest.h"

#include "ParticleDisplayList.h"

#include "../Math/ParticleBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(ParticleDisplayListTest, TestAdd)
{
	ParticleDisplayList list;
	ParticleBuilder builder(1.0f);
	Box b( Vector3d( 0.0f, 0.0f, 0.0f), Vector3d( 10.0f, 1.0f, 1.0f ) );
	const ParticleObject& object = builder.build(b.getInnerOffset(0.5f));
	list.add(object);

	EXPECT_EQ(30, list.getPositions().size());
	EXPECT_EQ(10, list.getIds().size());
}