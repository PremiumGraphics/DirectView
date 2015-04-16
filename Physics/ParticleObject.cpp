#include "ParticleObject.h"

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

void ParticleObject::remove(ParticleBase* particle)
{
	for (ParticleBase* p : particles) {
		if (p->getPosition() == particle->getPosition()) {
			particles.remove(p);
			break;
		}
	}
}

void ParticleObject::sub(const ParticleObject& rhs)
{
	for (ParticleBase* p : rhs.getParticles()) {
		remove(p);
	}
}

bool ParticleObject::isInner(ParticleBase* particle) const
{
	for (ParticleBase* p : particles) {
		if (p->getPosition() == particle->getPosition()) {
			return true;
		}
	}
	return false;
}

bool ParticleObject::isOuter(ParticleBase* particle) const
{
	return !isInner(particle);
}
