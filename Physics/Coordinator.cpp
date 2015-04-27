#include "Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void EulerIntegrator::coordinate(const PhysicsParticleSPtrVector& particles)
{
	for (const auto& particle : particles) {
		const auto& accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
		particle->addVelocity(accelaration * timeStep);
		particle->addCenter(particle->getVelocity() * timeStep);
	}
}


void ExternalForceCoordinator::coordinate(const PhysicsParticleSPtrVector& particles)
{
	for (const auto& particle : particles) {
		particle->addForce(force * particle->getDensity());
	}
}
