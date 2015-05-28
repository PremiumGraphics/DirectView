#include "gtest/gtest.h"

#include "../Physics/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST(PhysicsParticleConstantTest, TestConstruct)
{
	Particle<T>::Constant constant;
	EXPECT_EQ(1.0f, constant.getDiameter() );
	EXPECT_EQ(1.0f, constant.getRestDensity());
}


TEST(PhysicsParticleConstantTest, TestGetVolume)
{
	Particle<T>::Constant constant;
	constant.setDiameter(2.0f);
	EXPECT_FLOAT_EQ(8.0f, constant.getVolume());
}

TEST(PhysicsParticleTest, TestConstruct)
{
	const Particle<T> particle;
	EXPECT_EQ(Vector3d<T>(0.0f, 0.0f, 0.0f), particle.getCenter());
}

TEST(PhysicsParticleTest, TestConstructByPosition)
{
	const Particle<T> particle(Vector3d<T>(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(Vector3d<T>(1.0f, 2.0f, 3.0f), particle.getCenter());
}

TEST(PhysicsParticleTest, TestConstructByConstant)
{
	const Particle<T>::Constant constant;
	const Particle<T> particle(constant, Vector3d<T>( 0.0f, 0.0f, 0.0f ) );
}
