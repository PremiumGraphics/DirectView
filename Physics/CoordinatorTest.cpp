#include "gtest/gtest.h"
 
#include "Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( EulerIntegratorTest, Test )
{
	const PhysicsParticleSPtr particle = std::make_shared<PhysicsParticle>( Vector3d( 0.0, 0.0, 0.0 ) );
	particle->setVelocity(Vector3d(1.0f, 0.0f, 0.0f));
	EulerIntegrator integrator( 2.0f );
	PhysicsParticleSPtrVector particles{ particle };
	integrator.coordinate( particles );
	const auto actual = particle->getCenter();
	EXPECT_EQ(Vector3d(2.0f, 0.0f, 0.0), actual);
}

TEST( StaticIntegratorTest, Test )
{
	PhysicsParticle::Constant constant;
	const auto particle = std::make_shared<PhysicsParticle>(constant, Vector3d(0.0f, 0.0f, 0.0f));
	PhysicsParticleSPtrVector particles{ particle };
	StaticIntegrator integrator;
	integrator.coordinate( particles );
}