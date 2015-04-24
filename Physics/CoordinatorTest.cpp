#include "gtest/gtest.h"
 
#include "Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( EulerIntegratorTest, Test )
{
	PhysicsParticle::Constant constant;
	const PhysicsParticleSPtr& particle = std::make_shared<PhysicsParticle>( constant, Vector3d( 0.0, 0.0, 0.0 ) );
	EulerIntegrator integrator( 0.1 );
	PhysicsParticleSPtrVector particles;
	particles.push_back( particle );
	integrator.coordinate( particles );
}
