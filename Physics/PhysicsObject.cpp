#include "PhysicsObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float PhysicsObject::getMass() const
{
	auto weight = 0.0f;
	for (const auto& particle : particles) {
		weight += particle->getMass();
	}
	return weight;
}

float PhysicsObject::getVolume() const
{
	auto volume = 0.0f;
	for (const auto& particle : particles) {
		volume += particle->getVolume();
	}
	return volume;
}

void PhysicsObject::coordinate() const
{
	for (const auto& coordinator : coordinators) {
		coordinator->coordinate(particles);
	}
}
