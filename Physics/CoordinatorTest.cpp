#include "gtest/gtest.h"
 
#include "Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( EulerIntegratorTest, Test )
{
	PhysicsParticle::Constant constant;
	const PhysicsParticleSPtr particle = std::make_shared<PhysicsParticle>( constant, Vector3d( 0.0, 0.0, 0.0 ) );
	EulerIntegrator integrator( 0.1f );
	PhysicsParticleSPtrVector particles{ particle };
	integrator.coordinate( particles );
}

TEST( StaticIntegratorTest, Test )
{
	PhysicsParticle::Constant constant;
	const auto particle = std::make_shared<PhysicsParticle>(constant, Vector3d(0.0f, 0.0f, 0.0f));
	PhysicsParticleSPtrVector particles{ particle };
	StaticIntegrator integrator;
	integrator.coordinate( particles );
}