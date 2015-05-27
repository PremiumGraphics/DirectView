#include "gtest/gtest.h"

#include "../Physics/FluidObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST(FluidObjectTest, TestConstruct)
{
	FluidObject fluid;
	EXPECT_TRUE( fluid.getParticles().empty());
}

TEST(FluidObjectTest, TestConstructByParticles)
{
	const PhysicsParticleSPtrVector particles{
		std::make_shared<PhysicsParticle<T> >(Vector3d<T>(1.0f, 0.0f, 0.0f))
	};
	const FluidObject fluid(particles);
	EXPECT_EQ(1, fluid.getParticles().size());
}

TEST(FluidObjectTest, TestGetMass)
{
	const PhysicsParticleSPtrVector particles{
		std::make_shared<PhysicsParticle<T> >(Vector3d<T>(1.0f, 0.0f, 0.0f))
	};
	const FluidObject fluid(particles);
	EXPECT_FLOAT_EQ(1.0f, fluid.getMass());
}

TEST(FluidObjectTest, TestGetRestVolume)
{
	const PhysicsParticleSPtrVector particles{
		std::make_shared<PhysicsParticle<T> >(Vector3d<T>(1.0f, 0.0f, 0.0f))
	};
	const FluidObject fluid(particles);
	EXPECT_FLOAT_EQ(1.0f, fluid.getRestVolume());
}