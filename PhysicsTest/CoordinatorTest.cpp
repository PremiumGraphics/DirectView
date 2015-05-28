#include "gtest/gtest.h"
 
#include "../Physics/Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST( EulerIntegratorTest, Test )
{
	const ParticleSPtr particle = std::make_shared<Particle<T> >( Vector3d<T>( 0.0, 0.0, 0.0 ) );
	particle->setVelocity(Vector3d<T>(1.0f, 0.0f, 0.0f));
	EulerIntegrator integrator( 2.0f );
	ParticleSPtrVector particles{ particle };
	integrator.coordinate( particles );
	const auto actual = particle->getCenter();
	EXPECT_EQ(Vector3d<T>(2.0f, 0.0f, 0.0), actual);
}

TEST( StaticIntegratorTest, Test )
{
	Particle<T>::Constant constant;
	const auto particle = std::make_shared<Particle<T> >(constant, Vector3d<T>(0.0f, 0.0f, 0.0f));
	ParticleSPtrVector particles{ particle };
	StaticIntegrator integrator;
	integrator.coordinate( particles );
}