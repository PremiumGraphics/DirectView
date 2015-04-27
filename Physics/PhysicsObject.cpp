#include "PhysicsObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float PhysicsObject::getMass() const
{
	auto weight = 0.0;
	for (const PhysicsParticleSPtr& particle : particles) {
		weight += particle->getMass();
	}
	return weight;
}

void PhysicsObject::coordinate() const
{
	for (const auto& coordinator : coordinators) {
		coordinator->coordinate(particles);
	}
}
