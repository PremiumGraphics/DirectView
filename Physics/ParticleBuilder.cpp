#include "ParticleBuilder.h"

#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float ParticleObject::getVolume() const
{
	float volume = 0.0f;
	for (const ParticleBase& p : particles) {
		volume += p.getVolume();
	}
	return volume;
}

std::list<ParticleBase> ParticleBuilder::build(const Box& box)
{
	std::list<ParticleBase> particles;
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				ParticleBase p(divideLength, Vector3d(x, y, z));
				particles.push_back(p);
			}
		}
	}
	return particles;
}