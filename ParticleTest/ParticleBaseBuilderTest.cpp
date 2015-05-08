#include "gtest/gtest.h"

#include "../Particle/ParticleBaseBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleBaseBuilderTest, TestConstruct)
{
	ParticleBaseBuilder builder;
	EXPECT_EQ(1.0f, builder.getDensity());
	EXPECT_EQ(1.0f, builder.getDivideLength());
}

TEST(ParticleBaseBuilderTest, TestConstructByDivideLength)
{
	ParticleBaseBuilder builder(10.0f);
	EXPECT_EQ(1.0f, builder.getDensity());
	EXPECT_EQ(10.0f, builder.getDivideLength());
}

TEST(ParticleBaseBuilderTest, TestCreateBox)
{
	ParticleBaseBuilder builder( 1.0f );
	Box box(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0f, 1.0f, 1.0f));
	builder.create(box.getInnerOffset(0.5f));
	const ParticleBaseSPtrList& particles = builder.getParticles();
	EXPECT_EQ(10, particles.size());
}

TEST(ParticleBaseBuilderTest, TestCreateSphere)
{
	ParticleBaseBuilder builder(1.0f);
	const Sphere s(Vector3d(0.0, 0.0, 0.0), 1.0);
	builder.create(s);
	const ParticleBaseSPtrList& particles = builder.getParticles();
	EXPECT_EQ( 7, particles.size());
}

TEST(ParticleBaseBuilderTest, TestCreateCylinder)
{
	ParticleBaseBuilder builder(1.0f);
	const Cylinder c(Vector3d(0.0, 0.0, 0.0), 1.0f, 2.0f);
	builder.create(c);
	const ParticleBaseSPtrList& particles = builder.getParticles();
	EXPECT_FALSE( particles.empty() );
}