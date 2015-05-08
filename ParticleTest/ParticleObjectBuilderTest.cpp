#include <gtest/gtest.h>

#include "../Math/Cylinder.h"
#include "../Particle/ParticleObjectBuilder.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleObjectBuilderTest, TestConstruct)
{
	ParticleObjectBuilder builder;
	EXPECT_EQ(1.0f, builder.getDivideLength());
	EXPECT_EQ(1.0f, builder.getDensity());
	EXPECT_EQ(0, builder.getNextId());
}

TEST(ParticleObjectBuilderTest, TestConstructByDivideLength)
{
	ParticleObjectBuilder builder(10.0f);
	EXPECT_EQ(10.0f, builder.getDivideLength());
	EXPECT_EQ(1.0f, builder.getDensity());
	EXPECT_EQ(0, builder.getNextId());
}

TEST(ParticleObjectBuilderTest, TestConstructByDivideLengthAndDensity)
{
	ParticleObjectBuilder builder(10.0f, 5.0f);
	EXPECT_EQ(10.0f, builder.getDivideLength());
	EXPECT_EQ(5.0f, builder.getDensity());
	EXPECT_EQ(0, builder.getNextId());
}

TEST(ParticleObjectBuilderTest, TestBuildBox)
{
	ParticleObjectBuilder builder;
	const Box b(Vector3d( 0.0, 0.0, 0.0 ), Vector3d( 10.0f, 1.0f, 1.0f ));
	const auto actual = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, actual->getParticles().size());
}

TEST(ParticleObjectBuilderTest, TestBuildSphere)
{
	ParticleObjectBuilder builder;
	const Sphere s( Vector3d( 0.0, 0.0, 0.0), 10.0 );
	const auto actual = builder.build(s);
	EXPECT_FALSE(actual->getParticles().empty());
}

TEST(ParticleObjectBuilderTest, TestBuildCylinder)
{
	ParticleObjectBuilder builder;
	const Cylinder c( Vector3d( 0.0, 0.0, 0.0), 10.0f, 10.0f );
	const auto actual = builder.build(c);
	EXPECT_FALSE(actual->getParticles().empty());
}