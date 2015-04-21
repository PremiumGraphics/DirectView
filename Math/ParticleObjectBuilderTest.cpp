#include <gtest/gtest.h>
#include "ParticleObjectBuilder.h"

#include "../Math/Cylinder.h"

#include <memory>

using namespace Crystal::Math;

TEST(ParticleBaseTest, TestGetVolume)
{
	ParticleBase particle(1.0f, Vector3d( 0.0f, 0.0f, 0.0f), 0 );
	EXPECT_FLOAT_EQ( 1.0f, particle.getVolume() );
}

TEST(ParticleObjectBuilderTest, TestBuildBox)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b(Vector3d( 0.0, 0.0, 0.0 ), Vector3d( 10.0f, 1.0f, 1.0f ));
	ParticleObjectSPtr actual = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, actual->getParticles().size());
}

TEST(ParticleObjectBuilderTest, TestBuildSphere)
{
	ParticleObjectBuilder builder(1.0f);
	const Sphere s( Vector3d( 0.0, 0.0, 0.0), 10.0 );
	ParticleObjectSPtr actual = builder.build(s);
	EXPECT_FALSE(actual->getParticles().empty());
}

TEST(ParticleObjectBuilderTest, TestBuildCylinder)
{
	ParticleObjectBuilder builder(1.0f);
	const Cylinder c( Vector3d( 0.0, 0.0, 0.0), 10.0f, 10.0f );
	ParticleObjectSPtr actual = builder.build(c);
	EXPECT_FALSE(actual->getParticles().empty());
}

/*
TEST(ParticleObjectBuilderTest, TestGetObject)
{
	ParticleObjectBuilder builder(1.0f);
	const Cylinder c(Vector3d(0.0, 0.0, 0.0), 10.0f, 10.0f);
	ParticleObjectSPtr o1 = builder.build(c);

	const Box b(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0, 0.0, 0.0));
	ParticleObjectSPtr o2 = builder.build(b);

	EXPECT_EQ(o1, builder.getObject(0));
	EXPECT_EQ(o2, builder.getObject(1));
	EXPECT_EQ(nullptr, builder.getObject(2));
}
*/