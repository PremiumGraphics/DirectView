#ifndef __CRYSTAL_PHYSICS_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_COORDINATOR_H__

#include <vector>

#include "Particle.h"

#include "../Math/Vector3d.h"

namespace Crystal{
	namespace Physics{

class Coordinator
{
public:
	Coordinator(){};

	virtual ~Coordinator(){}

	virtual void coordinate( const ParticleSPtrVector& particles ) = 0;

protected:
	float timeStep;
};

typedef std::vector<Coordinator*> CoordinatorVector;

class StaticIntegrator : public Coordinator
{
public:
	void coordinate( const ParticleSPtrVector& particles){}
};

class EulerIntegrator : public Coordinator
{
public:
	EulerIntegrator(const float timeStep) :
		timeStep( timeStep )
	{
	}
	void coordinate( const ParticleSPtrVector& particles ) {
		for( const ParticleSPtr& particle : particles ) {
			Math::Vector3d accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
			particle->addVelocity( accelaration * timeStep );
			particle->addCenter( particle->getVelocity() * timeStep );
		}
	}

private:
	float timeStep;
};


class ExternalForceCoordinator : public Coordinator
{
public:
	ExternalForceCoordinator(const Math::Vector3d& force, const float timeStep) :
		force( force ),
		timeStep( timeStep )
	{}

	void coordinate( const std::list<ParticleSPtr>& particles ) {
		for( const ParticleSPtr& particle : particles ) {
			particle->addForce( force * particle->getDensity() );
		}
	}

	Math::Vector3d getForce() const { return force; }

	void addForce( const Math::Vector3d& force ) { this->force += force; }

private:
	Math::Vector3d force;
	float timeStep;
};

	}
}

#endif