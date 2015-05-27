#include "gtest/gtest.h"
 
#include "../Physics/Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST( EulerIntegratorTest, Test )
{
	const PhysicsParticleSPtr particle = std::make_shared<PhysicsParticle<T> >( Vector3d<T>( 0.0, 0.0, 0.0 ) );
	particle->setVelocity(Vector3d<T>(1.0f, 0.0f, 0.0f));
	EulerIntegrator integrator( 2.0f );
	PhysicsParticleSPtrVector particles{ particle };
	integrator.coordinate( particles );
	const auto actual = particle->getCenter();
	EXPECT_EQ(Vector3d<T>(2.0f, 0.0f, 0.0), actual);
}

TEST( StaticIntegratorTest, Test )
{
	PhysicsParticle<T>::Constant constant;
	const auto particle = std::make_shared<PhysicsParticle<T> >(constant, Vector3d<T>(0.0f, 0.0f, 0.0f));
	PhysicsParticleSPtrVector particles{ particle };
	StaticIntegrator integrator;
	integrator.coordinate( particles );
}