#include "../Particle/ParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

bool CollisionFindAlgo::hasCollision(const ParticleBasePair& pair, const float threshold)
{
	return pair.getDistance() < threshold;
}