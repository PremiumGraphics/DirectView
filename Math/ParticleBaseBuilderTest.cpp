#include "gtest/gtest.h"

#include "../Math/ParticleBaseBuilder.h"

using namespace Crystal::Math;

TEST(ParticleBaseBuilderTest, TestCreateBox)
{
	ParticleBaseBuilder builder( 1.0f );
	Box box(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0f, 1.0f, 1.0f));
	const std::list<ParticleBaseSPtr>& particles = builder.create(box.getInnerOffset(0.5f));
	EXPECT_EQ(10, particles.size());
}