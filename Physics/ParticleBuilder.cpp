#include "ParticleBuilder.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"

#include "../Particle/ParticleBase.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

ParticleSPtr ParticleBuilder::create(const ParticleBase& origin)
{
	return std::make_shared<Particle>(constant, origin.getPosition());
}

ParticleSPtrVector ParticleBuilder::create(const Box& box)
{
	ParticleSPtrVector particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				particles.push_back(std::make_shared<Particle>(constant, Vector3d(x, y, z)));
				//object->add(p);
			}
		}
	}
	return particles;
}

ParticleSPtrVector ParticleBuilder::create(const Sphere& s)
{
	ParticleSPtrVector particles;
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (s.isInner(v)) {
					particles.push_back(std::make_shared<Particle>(constant, Vector3d(x, y, z)));
				}
			}
		}
	}
	return particles;
}