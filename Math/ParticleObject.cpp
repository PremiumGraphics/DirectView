#include "ParticleObject.h"

using namespace Crystal::Math;

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

Box ParticleObject::getBoundingBox() const
{
	Box b(particles.front()->getPosition(), particles.back()->getPosition());
	for (ParticleBase* p : particles) {
		b.add(p->getPosition());
	}
	return b;
}

std::list<ParticleBase*> ParticleBooleanAlgo::createUnion(const ParticleObject& lhs, const ParticleObject& rhs)
{
	std::list<ParticleBase*> particles1 = lhs.getParticles();
	const std::list<ParticleBase*> particles2 = rhs.getParticles();

	particles1.insert(particles1.end(), particles2.begin(), particles2.end());
	return particles1;
}

std::list<ParticleBase*> ParticleBooleanAlgo::createIntersection(const ParticleObject& lhs, const ParticleObject& rhs)
{
	std::list<ParticleBase*> particles;
	for (ParticleBase* p1 : lhs.getParticles()) {
		for (ParticleBase* p2 : rhs.getParticles()) {
			if (p1->getPosition() == p2->getPosition()) {
				particles.push_back(p1);
			}
		}
	}
	return particles;
}

std::list<ParticleBase*> ParticleBooleanAlgo::createDiff(const ParticleObject& lhs, const ParticleObject& rhs)
{
	std::list<ParticleBase*> particles = lhs.getParticles();

	std::list<ParticleBase*> intersects = createIntersection( lhs, rhs );

	for (ParticleBase* p2 : intersects) {
		for (std::list<ParticleBase*>::iterator iter = particles.begin(); iter != particles.end();) {
			ParticleBase* p1 = (*iter);
			if (p1->getPosition() == p2->getPosition()) {
				iter = particles.erase(iter);
				continue;
			}
			++iter;
		}
	}
	return particles;
}

std::vector< float > ParticleObject::toPositionArray() const
{
	std::vector< float > results;
	for (ParticleBase* p : particles) {
		std::vector<float> pos = p->getPosition().toArray();
		results.insert(results.end(), pos.begin(), pos.end());
	}
	return results;
}

std::vector< unsigned int > ParticleObject::toIdArray() const
{
	std::vector< unsigned int > results;
	for (ParticleBase* p : particles) {
		results.push_back(p->getId());
	}
	return results;
}
