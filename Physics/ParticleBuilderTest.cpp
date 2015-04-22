#include "gtest/gtest.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"

#include "ParticleBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(ParticleBuilderTest, TestBuildBox)
{
	ParticleBuilder builder;
	const Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const ParticleSPtrVector& actual = builder.create(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, actual.size());
}

TEST(ParticleBuilderTest, TestCreateSphere)
{
	ParticleBuilder builder;
	const Sphere s(Vector3d(0.0, 0.0, 0.0), 1.0);
	const ParticleSPtrVector& particles = builder.create(s);
	EXPECT_EQ(7, particles.size());
}
