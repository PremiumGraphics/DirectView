#include "ParticleBuilder.h"

#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


void ParticleBuilder::clear()
{
	for (ParticleBase * p : particles) {
		delete p;
	}
	particles.clear();
}

ParticleObject ParticleBuilder::build(const Box& box)
{
	ParticleObject object;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				ParticleBase* p = new ParticleBase(divideLength, Vector3d(x, y, z), nextId++);
				particles.push_back(p);
				object.add(p);
			}
		}
	}
	return object;
}

ParticleObject ParticleBuilder::build(const Sphere& s)
{
	ParticleObject object;
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (s.isInner(v)) {
					ParticleBase* p = new ParticleBase(divideLength, v, nextId++ );
					particles.push_back(p);
					object.add(p);
				}
			}
		}
	}
	return object;
}

ParticleObject ParticleBuilder::build(const Cylinder& c)
{
	ParticleObject object;
	Box box = c.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (c.isInner(v)) {
					ParticleBase* p = new ParticleBase(divideLength, v, nextId++);
					particles.push_back(p);
					object.add(p);
				}
			}
		}
	}
	return object;

}
