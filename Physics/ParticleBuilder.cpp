#include "ParticleBuilder.h"

#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float ParticleObject::getVolume() const
{
	float volume = 0.0f;
	for (ParticleBase* p : particles) {
		volume += p->getVolume();
	}
	return volume;
}

/*
void ParticleObject::add(const ParticleObject& rhs)
{
	;
}

void ParticleObject::intersection(const ParticleObject& rhs)
{
	;
}
*/

void ParticleObject::sub(ParticleBase* particle)
{
	for (ParticleBase* p : particles) {
		if (p->getPosition() == particle->getPosition() ) {
			particles.remove(p);
			break;
		}
	}
}

void ParticleObject::sub(const ParticleObject& rhs)
{
	for (ParticleBase* p : rhs.getParticles()) {
		sub(p);
	}
}


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
				ParticleBase* p = new ParticleBase(divideLength, Vector3d(x, y, z));
				particles.push_back(p);
				object.add(p);
			}
		}
	}
	return object;
}

/*
ParticleObject ParticleBuilder::build(const Math::Sphere& s)
{
	std::list<ParticleBase> particles = build( s.getBoundingBox() );

	for (const ParticleBase& p : particles) {
		const Vector3d& v = p.getPosition();
		if (s.isInner(v)) {
			particles.remove(v);
		}
	}
	ParticleObject object;;
}
*/
