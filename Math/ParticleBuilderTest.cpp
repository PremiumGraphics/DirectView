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

TEST(ParticleBuilderTest, TestBuildBox)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b(Vector3d( 0.0, 0.0, 0.0 ), Vector3d( 10.0f, 1.0f, 1.0f ));
	ParticleObject* actual = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, actual->getParticles().size());
}

TEST(ParticleBuilderTest, TestBuildSphere)
{
	ParticleObjectBuilder builder(1.0f);
	const Sphere s( Vector3d( 0.0, 0.0, 0.0), 10.0 );
	builder.build(s);
	EXPECT_FALSE(builder.getParticles().empty());
}

TEST(ParticleBuilderTest, TestBuildCylinder)
{
	ParticleObjectBuilder builder(1.0f);
	const Cylinder c( Vector3d( 0.0, 0.0, 0.0), 10.0f, 10.0f );
	builder.build(c);
	EXPECT_FALSE(builder.getParticles().empty());
}