#include "gtest/gtest.h"

#include "../Physics/PhysicsParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(PhysicsParticleConstantTest, TestConstruct)
{
	PhysicsParticle::Constant constant;
	EXPECT_EQ(1.0f, constant.getDiameter() );
	EXPECT_EQ(1.0f, constant.getRestDensity());
}


TEST(PhysicsParticleConstantTest, TestGetVolume)
{
	PhysicsParticle::Constant constant;
	constant.setDiameter(2.0f);
	EXPECT_FLOAT_EQ(8.0f, constant.getVolume());
}

TEST(PhysicsParticleTest, TestConstruct)
{
	const PhysicsParticle particle;
	EXPECT_EQ(Vector3d(0.0f, 0.0f, 0.0f), particle.getCenter());
}

TEST(PhysicsParticleTest, TestConstructByPosition)
{
	const PhysicsParticle particle(Vector3d(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(Vector3d(1.0f, 2.0f, 3.0f), particle.getCenter());
}

TEST(PhysicsParticleTest, TestConstructByConstant)
{
	const PhysicsParticle::Constant constant;
	const PhysicsParticle particle(constant, Vector3d( 0.0f, 0.0f, 0.0f ) );
}
