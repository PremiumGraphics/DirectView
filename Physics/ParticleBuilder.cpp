#include "ParticleBuilder.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

#include "../Particle/ParticleBase.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;
using namespace Crystal::Physics;

PhysicsParticleSPtr ParticleBuilder::create(const ParticleBase& origin)
{
	return std::make_shared<PhysicsParticle>(constant, origin.getPosition());
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Box& box)
{
	PhysicsParticleSPtrVector particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				particles.push_back(std::make_shared<PhysicsParticle>(constant, Vector3d(x, y, z)));
				//object->add(p);
			}
		}
	}
	return particles;
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Sphere& s)
{
	PhysicsParticleSPtrVector particles;
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (s.isInner(v)) {
					particles.push_back(std::make_shared<PhysicsParticle>(constant, Vector3d(x, y, z)));
				}
			}
		}
	}
	return particles;
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Cylinder& cylinder)
{
	const Box& box = cylinder.getBoundingBox();
	Vector3dVector positions;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (cylinder.isInner(v)) {
					positions.push_back(v);
				}
			}
		}
	}
	return create( positions );
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Vector3dVector& positions)
{
	PhysicsParticleSPtrVector particles;
	for (const Vector3d& p : positions) {
		particles.push_back(std::make_shared<PhysicsParticle>(constant, p) );
	}
	return particles;
}
