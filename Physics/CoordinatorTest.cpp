#include "gtest/gtest.h"
 
#include "Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( EulerIntegratorTest, Test )
{
	Particle::Constant constant;
	Particle particle( constant, Vector3d( 0.0, 0.0, 0.0 ) );
	EulerIntegrator integrator( 0.1 );
	ParticleVector particles;
	particles.push_back( &particle );
	integrator.coordinate( particles );
}
