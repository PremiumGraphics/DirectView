#include "ParticleBuilder.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


PhysicsParticleSPtrVector ParticleBuilder::create(const Box& box)
{
	PhysicsParticleSPtrVector particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				particles.push_back(std::make_shared<PhysicsParticle<float> >(constant, Vector3d<float>(x, y, z)));
				//object->add(p);
			}
		}
	}
	return particles;
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Sphere<float>& s)
{
	PhysicsParticleSPtrVector particles;
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d<float> v(x, y, z);
				if (s.isInner(v)) {
					particles.push_back(std::make_shared<PhysicsParticle<float> >(constant, Vector3d<float>(x, y, z)));
				}
			}
		}
	}
	return particles;
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Cylinder<float>& cylinder)
{
	const Box& box = cylinder.getBoundingBox();
	Vector3dVector<float> positions;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d<float> v(x, y, z);
				if (cylinder.isInner(v)) {
					positions.push_back(v);
				}
			}
		}
	}
	return create( positions );
}

PhysicsParticleSPtrVector ParticleBuilder::create(const Vector3dVector<float>& positions)
{
	PhysicsParticleSPtrVector particles;
	for (const Vector3d<float>& p : positions) {
		particles.push_back(std::make_shared<PhysicsParticle<float> >(constant, p) );
	}
	return particles;
}
