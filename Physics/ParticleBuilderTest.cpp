#include <gtest/gtest.h>
#include "ParticleBuilder.h"

#include "../Math/Cylinder.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(ParticleBaseTest, TestGetVolume)
{
	ParticleBase particle(1.0f, Vector3d( 0.0f, 0.0f, 0.0f), 0 );
	EXPECT_FLOAT_EQ( 1.0f, particle.getVolume() );
}

TEST(ParticleBuilderTest, TestBuildBox)
{
	ParticleBuilder builder(1.0f);
	const Box b(Vector3d( 0.0, 0.0, 0.0 ), Vector3d( 10.0f, 1.0f, 1.0f ));
	const ParticleObject& actual = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, actual.getParticles().size());
}

TEST(ParticleBuilderTest, TestBuildSphere)
{
	ParticleBuilder builder(1.0f);
	const Sphere s( Vector3d( 0.0, 0.0, 0.0), 10.0 );
	builder.build(s);
	EXPECT_FALSE(builder.getParticles().empty());
}

TEST(ParticleBuilderTest, TestBuildCylinder)
{
	ParticleBuilder builder(1.0f);
	const Cylinder c( Vector3d( 0.0, 0.0, 0.0), 10.0f, 10.0f );
	builder.build(c);
	EXPECT_FALSE(builder.getParticles().empty());
}