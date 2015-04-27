#include "../Particle/ParticleBasePair.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

bool ParticleBasePair::isValid() const
{
	return
		(particle1 != nullptr) &&
		(particle2 != nullptr) &&
		(particle1 != particle2);
}

Vector3d ParticleBasePair::getDistanceVector() const
{
	return Math::Vector3d(particle1->getPosition() - particle2->getPosition());
}

float ParticleBasePair::getDistance() const
{
	return particle1->getPosition().getDistance(particle2->getPosition());
}

bool ParticleBasePair::isNeighbor() const
{
	const float threshold = particle1->getRadius() + particle2->getRadius();
	return getDistance() < threshold;
}
