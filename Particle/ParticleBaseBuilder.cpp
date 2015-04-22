#include "ParticleBaseBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

std::list<ParticleBaseSPtr> ParticleBaseBuilder::create(const Box& box)
{
	std::list< ParticleBaseSPtr > particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				particles.push_back(std::make_shared<ParticleBase>(divideLength, Vector3d(x, y, z), density, nextId++));
				//object->add(p);
			}
		}
	}
	return particles;
}

std::list<ParticleBaseSPtr> ParticleBaseBuilder::create(const Sphere& s)
{
	std::list< ParticleBaseSPtr > particles;
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (s.isInner(v)) {
					particles.push_back(std::make_shared<ParticleBase>(divideLength, v, density, nextId++));
				}
			}
		}
	}
	return particles;
}

std::list<ParticleBaseSPtr> ParticleBaseBuilder::create(const Cylinder& c)
{
	std::list< ParticleBaseSPtr > particles;
	Box box = c.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (c.isInner(v)) {
					particles.push_back(std::make_shared<ParticleBase>(divideLength, v, density, nextId++));
				}
			}
		}
	}
	return particles;
}
