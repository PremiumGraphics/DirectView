#include "ParticleBaseBuilder.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Particle;

void ParticleBaseBuilder::create(const Box& box)
{
	for (auto x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (auto y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (auto z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const auto p = std::make_shared<ParticleBase>(divideLength, Vector3d(x, y, z), density, nextId++);
				particles.push_back(p);
			}
		}
	}
}

void ParticleBaseBuilder::create(const Sphere& s)
{
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
}

void ParticleBaseBuilder::create(const Cylinder& c)
{
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
}