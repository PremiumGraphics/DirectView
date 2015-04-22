#include "PhysicsObjectBuilder.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

std::list<ParticleSPtr> PhysicsObjectBuilder::create(const Box& box)
{
	Particle::Constant constant;
	std::list< ParticleSPtr > particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				particles.push_back( std::make_shared<Particle>( constant, Vector3d(x, y, z) ) );
				//object->add(p);
			}
		}
	}
	return particles;

}