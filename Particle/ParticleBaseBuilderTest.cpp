#include "gtest/gtest.h"

#include "ParticleBaseBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleBaseBuilderTest, TestCreateBox)
{
	ParticleBaseBuilder builder( 1.0f );
	Box box(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0f, 1.0f, 1.0f));
	const std::list<ParticleBaseSPtr>& particles = builder.create(box.getInnerOffset(0.5f));
	EXPECT_EQ(10, particles.size());
}

TEST(ParticleBaseBuilderTest, TestCreateSphere)
{
	ParticleBaseBuilder builder(1.0f);
	const Sphere s(Vector3d(0.0, 0.0, 0.0), 1.0);
	const std::list<ParticleBaseSPtr>& particles = builder.create(s);
	EXPECT_EQ( 7, particles.size());
}

TEST(ParticleBaseBuilderTest, TestCreateCylinder)
{
	ParticleBaseBuilder builder(1.0f);
	const Cylinder c(Vector3d(0.0, 0.0, 0.0), 1.0f, 2.0f);
	const std::list<ParticleBaseSPtr>& particles = builder.create(c);
	EXPECT_FALSE( particles.empty() );
}