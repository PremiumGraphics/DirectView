#include "PhysicsObjectBuilder.h"

#include "PhysicsObject.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

PhysicsObjectSPtr PhysicsObjectBuilder::create(const Box& box)
{
	PhysicsParticle::Constant constant;
	ParticleSPtrVector particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				particles.push_back( std::make_shared<PhysicsParticle>( constant, Vector3d(x, y, z) ) );
				//object->add(p);
			}
		}
	}
	return std::make_shared<PhysicsObject>(particles);
}