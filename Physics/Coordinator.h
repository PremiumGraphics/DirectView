#ifndef __CRYSTAL_PHYSICS_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_COORDINATOR_H__

#include <vector>

#include "PhysicsParticle.h"

#include "../Math/Vector3d.h"

#include "../Util/UnCopyable.h"

namespace Crystal{
	namespace Physics{

class Coordinator : private UnCopyable
{
public:
	Coordinator(){};

	virtual ~Coordinator(){}

	virtual void coordinate( const PhysicsParticleSPtrVector& particles ) = 0;

protected:
	float timeStep;
};

typedef std::vector<Coordinator*> CoordinatorVector;

class StaticIntegrator final : public Coordinator
{
public:
	virtual void coordinate( const PhysicsParticleSPtrVector& particles) override
	{}
};

class EulerIntegrator final : public Coordinator
{
public:
	EulerIntegrator(const float timeStep) :
		timeStep( timeStep )
	{
	}
	
	virtual void coordinate( const PhysicsParticleSPtrVector& particles ) override {
		for( const PhysicsParticleSPtr& particle : particles ) {
			Math::Vector3d accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
			particle->addVelocity( accelaration * timeStep );
			particle->addCenter( particle->getVelocity() * timeStep );
		}
	}

private:
	float timeStep;
};


class ExternalForceCoordinator final : public Coordinator
{
public:
	ExternalForceCoordinator(const Math::Vector3d& force, const float timeStep) :
		force( force ),
		timeStep( timeStep )
	{}

	virtual void coordinate(const PhysicsParticleSPtrVector& particles) override;

	Math::Vector3d getForce() const { return force; }

	void addForce( const Math::Vector3d& force ) { this->force += force; }

private:
	Math::Vector3d force;
	float timeStep;
};

	}
}

#endif