#include "gtest/gtest.h"
 
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( ParticleTest, Test )
{
	Particle::Constant constant;
	Particle particle( constant, Vector3d( 0.0, 0.0, 0.0 ) );
}
