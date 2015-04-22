#include "ParticleBooleanAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

std::list<ParticleBaseSPtr> ParticleBooleanAlgo::createUnion(const ParticleObject& lhs, const ParticleObject& rhs)
{
	std::list<ParticleBaseSPtr> particles1 = lhs.getParticles();
	const std::list<ParticleBaseSPtr> particles2 = rhs.getParticles();

	particles1.insert(particles1.end(), particles2.begin(), particles2.end());
	return particles1;
}

std::list<ParticleBaseSPtr> ParticleBooleanAlgo::createIntersection(const ParticleObject& lhs, const ParticleObject& rhs)
{
	std::list<ParticleBaseSPtr> particles;
	for (ParticleBaseSPtr p1 : lhs.getParticles()) {
		for (ParticleBaseSPtr p2 : rhs.getParticles()) {
			if (p1->getPosition() == p2->getPosition()) {
				particles.push_back(p1);
			}
		}
	}
	return particles;
}

std::list<ParticleBaseSPtr> ParticleBooleanAlgo::createDiff(const ParticleObject& lhs, const ParticleObject& rhs)
{
	std::list<ParticleBaseSPtr> particles = lhs.getParticles();

	std::list<ParticleBaseSPtr> intersects = createIntersection(lhs, rhs);

	for (ParticleBaseSPtr p2 : intersects) {
		for (std::list<ParticleBaseSPtr>::iterator iter = particles.begin(); iter != particles.end();) {
			ParticleBaseSPtr p1 = (*iter);
			if (p1->getPosition() == p2->getPosition()) {
				iter = particles.erase(iter);
				continue;
			}
			++iter;
		}
	}
	return particles;
}
