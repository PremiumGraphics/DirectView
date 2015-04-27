#ifndef __CRYSTAL_PHYSICS_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_COORDINATOR_H__

#include <vector>

#include "PhysicsParticle.h"

#include "../Math/Vector3d.h"

#include "../Util/UnCopyable.h"

#include <memory>

namespace Crystal{
	namespace Physics{

class Coordinator : private UnCopyable
{
public:
	Coordinator()
	{};

	virtual ~Coordinator(){}

	virtual void coordinate( const PhysicsParticleSPtrVector& particles ) = 0;
};

using CoordinatorSPtr = std::shared_ptr < Coordinator > ;
using CoordinatorSPtrVector = std::vector<CoordinatorSPtr>;

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
	
	virtual void coordinate(const PhysicsParticleSPtrVector& particles) override;

	float getTimeStep() const { return timeStep; }

private:
	const float timeStep;
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

	float getTimeStep() const { return timeStep; }

private:
	Math::Vector3d force;
	const float timeStep;
};

	}
}

#endif