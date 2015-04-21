#include "gtest/gtest.h"

#include "../Math/ParticleBase.h"

using namespace Crystal::Math;

TEST(ParticleBaseTest, TestConstruct )
{
	ParticleBase p(1.0f, Vector3d( 0.0f, 0.0f, 0.0f), 0);
	EXPECT_EQ(1.0f, p.getDensity());
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), p.getPosition());
	EXPECT_EQ(1.0f, p.getVolume());
}