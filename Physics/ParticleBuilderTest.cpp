#include <gtest/gtest.h>
#include "ParticleBuilder.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(ParticleBaseTest, TestGetVolume)
{
	ParticleBase particle(1.0f, Vector3d( 0.0f, 0.0f, 0.0f) );
	EXPECT_FLOAT_EQ( 1.0f, particle.getVolume() );
}

TEST(ParticleObjectTest, TestAdd)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f));
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());
}

TEST(ParticleObjectTest, TestSub)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f));
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());
	ParticleBase particle1(1.0f, Vector3d(0.0f, 0.0f, 0.0f));
	object.sub(&particle1);
	EXPECT_TRUE(object.getParticles().empty());
}

TEST(ParticleObjectTest, TestSub2)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f));
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());
	ParticleBase particle1(1.0f, Vector3d(0.0f, 0.0f, 0.0f));
	ParticleObject rhs;
	rhs.add(&particle1);
	object.sub(rhs);
	EXPECT_TRUE(object.getParticles().empty());
}


TEST(ParticleBuilderTest, TestBuildBox)
{
	ParticleBuilder builder(1.0f);
	const Box b(Vector3d( 0.0, 0.0, 0.0 ), Vector3d( 10.0f, 1.0f, 1.0f ));
	const ParticleObject& actual = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, actual.getParticles().size());
}

/*
TEST(ParticleBuilderTest, TestBuildCircle)
{
	ParticleBuilder builder(1.0f);
	..const Circle c()
	builder.build()
}
*/