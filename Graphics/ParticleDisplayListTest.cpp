#include "gtest/gtest.h"

#include "ParticleDisplayList.h"

#include "../Particle/ParticleObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;
using namespace Crystal::Graphics;

TEST(ParticleDisplayList, TestConstruct)
{
	ParticleDisplayList list;
	EXPECT_TRUE(list.getPositions().empty());
}

TEST(ParticleDisplayList, TestToColor)
{
	{
		ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
		ParticleDisplayList list;
		const ColorRGB<float>& actual = list.toColor(particle);
		const ColorRGB<float> expected(0.0f, 0.0f, 0.0f);
		EXPECT_EQ(expected, actual);
	}
}

TEST(ParticleDisplayListTest, TestAdd)
{
	ParticleDisplayList list;
	ParticleObjectBuilder builder(1.0f);
	Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr object = builder.build(b.getInnerOffset(0.5f));
	list.add(*object);

	EXPECT_EQ(30, list.getPositions().size());
	EXPECT_EQ(30, list.getColors().size());
}