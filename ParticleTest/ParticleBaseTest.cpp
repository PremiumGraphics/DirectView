#include "gtest/gtest.h"

#include "../Particle/ParticleBase.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleBaseTest, TestConstruct)
{
	ParticleBase p;
	EXPECT_EQ(1.0f, p.getDensity());
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), p.getPosition());
	EXPECT_EQ(-1, p.getId());
}

TEST(ParticleBaseTest, TestConstructByDiameter)
{
	ParticleBase p(10.0f);
	EXPECT_EQ(1.0f, p.getDensity());
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), p.getPosition());
}

TEST(ParticleBaseTest, TestConstructByPosition)
{
	ParticleBase p( Vector3d(1.0f, 0.0f, 0.0f) );
	EXPECT_EQ(1.0f, p.getDensity());
	EXPECT_EQ(Vector3d(1.0f, 0.0f, 0.0f), p.getPosition());
}

TEST(ParticleBaseTest, TestConstructByDiameterPositionId)
{
	ParticleBase p(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	EXPECT_EQ(1.0f, p.getDensity());
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), p.getPosition());
}

TEST(ParticleBaseTest, TestGetRadius)
{
	ParticleBase p;
	EXPECT_FLOAT_EQ(0.5f, p.getRadius());
}

TEST(ParticleBaseTest, TestGetVolume)
{
	ParticleBase particle(10.0f);
	EXPECT_FLOAT_EQ(1000.0f, particle.getVolume());
}

TEST(ParticleBaseTest, TestToBox)
{
	ParticleBase p(2.0f);
	const auto box = p.toBox();
	EXPECT_EQ( Position3d<float>(-1.0f, -1.0f, -1.0f), box.getMin() );
	EXPECT_EQ( Position3d<float>(1.0f, 1.0f, 1.0f), box.getMax() );
}