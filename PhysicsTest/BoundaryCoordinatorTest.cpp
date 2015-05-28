#include "gtest/gtest.h"
 
#include "../Physics/BoundaryCoordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
using T = float;

TEST( BoundaryCoordinatorTest, Test )
{
	const ParticleSPtr particle = std::make_shared<Particle<T> >( Vector3d<T>( 0.0, 0.0, 0.0 ) );
	const ParticleSPtrVector particles{ particle };

	BoundaryCoordinator<T> coordinator( Box<T>::Unit(), 1.0f);
	coordinator.coordinate(particles);
	//BoundaryCoordinator b;
}
