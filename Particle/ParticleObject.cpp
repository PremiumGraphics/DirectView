#include "ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

float ParticleObject::getVolume() const
{
	float volume = 0.0f;
	for (ParticleBaseSPtr p : particles) {
		volume += p->getVolume();
	}
	return volume;
}

float ParticleObject::getMass() const
{
	float mass = 0.0f;
	for (const ParticleBaseSPtr& p : particles) {
		mass += p->getMass();
	}
	return mass;
}

void ParticleObject::remove(ParticleBaseSPtr particle)
{
	for (ParticleBaseSPtr p : particles) {
		if (p->getPosition() == particle->getPosition()) {
			particles.remove(p);
			break;
		}
	}
}

void ParticleObject::sub(const ParticleObject& rhs)
{
	for (ParticleBaseSPtr p : rhs.getParticles()) {
		remove(p);
	}
}


bool ParticleObject::isInner(ParticleBase* particle) const
{
	for (ParticleBaseSPtr p : particles) {
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

Box ParticleObject::getBoundingBox() const
{
	Box b(particles.front()->getPosition(), particles.back()->getPosition());
	for (ParticleBaseSPtr p : particles) {
		b.add(p->getPosition());
	}
	return b;
}

bool ParticleObject::hasSelfIntersection() const
{
	for (const ParticleBaseSPtr& p1 : particles) {
		for (const ParticleBaseSPtr& p2 : particles) {
			if (p1 == p2){
				continue;
			}
			if (p1->getPosition() == p2->getPosition()) {
				return true;
			}
		}
	}
	return false;
}

std::vector<float> ParticleObject::toPositionArray() const
{
	std::vector< float > results;
	for (ParticleBaseSPtr p : particles) {
		std::vector<float> pos = p->getPosition().toArray();
		results.insert(results.end(), pos.begin(), pos.end());
	}
	return results;
}

std::vector< unsigned int > ParticleObject::toIdArray() const
{
	std::vector< unsigned int > results;
	for (ParticleBaseSPtr p : particles) {
		results.push_back(p->getId());
	}
	return results;
}
