#include "ParticleBase.h"

using namespace Crystal::Math;

std::vector<ParticleBase*> ParticleBuilder::create(const Box& box)
{
	std::vector< ParticleBase* > particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				ParticleBase* p = new ParticleBase(divideLength, Vector3d(x, y, z), nextId++);
				particles.push_back(p);
				//object->add(p);
			}
		}
	}
	return particles;
}

std::vector<ParticleBase*> ParticleBuilder::create(const Sphere& s)
{
	std::vector< ParticleBase* > particles;
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (s.isInner(v)) {
					ParticleBase* p = new ParticleBase(divideLength, v, nextId++);
					particles.push_back(p);
				}
			}
		}
	}
	return particles;
}

std::vector<ParticleBase*> ParticleBuilder::create(const Cylinder& c)
{
	std::vector< ParticleBase* > particles;
	Box box = c.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (c.isInner(v)) {
					ParticleBase* p = new ParticleBase(divideLength, v, nextId++);
					particles.push_back(p);
				}
			}
		}
	}
	return particles;
}
