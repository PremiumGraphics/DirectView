#ifndef __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__

#include "Coordinator.h"

#include "../Math/Box.h"

#include <vector>

namespace Crystal{
	namespace Physics{

class BoundaryCoordinator : public Coordinator
{
public:
	BoundaryCoordinator(const Math::Box<float>& box, const float timeStep ) :
		box( box ),
		timeStep( timeStep )
	{}

	~BoundaryCoordinator(void){};

	virtual void coordinate(const PhysicsParticleSPtrVector& particles);

private:
	const Math::Box<float> box;
	const float timeStep;

	Math::Vector3d<float> getForce(const Math::Vector3d<float>& center, const Math::Box<float>& box) {
		Math::Vector3d<float> force = Math::Vector3d<float>::Zero();

		force += getForceX(center.getX(), box );
		force += getForceY(center.getY(), box, timeStep);
		force += getForceZ(center.getZ(), box, timeStep);

		return force;

	}

	Math::Vector3d<float> getForceX(const float x, const Math::Box<float>& box) {
		float over = 0.0f;
		if (x > box.getMaxX()) {
			over = x - box.getMaxX();
		}
		else if (x < box.getMinX()) {
			over = x - box.getMinX();
		}

		const float force = getForce(over);
		return Math::Vector3d<float>::UnitX() * force;
	}

	Math::Vector3d<float> getForceY(const float y, const Math::Box<float>& box, const float timeStep);

	Math::Vector3d<float> getForceZ(const float z, const Math::Box<float>& box, const float timeStep);

	float getForce(const float over) {
		return -over / timeStep / timeStep;
	}


};

/*
class SphereBoundaryCoordinator : public Coordinator
{
public:
	SphereBoundaryCoordinator(const float radius, const Math::Vector3d& center) :
		radius( radius ),
		center( center )
	{}

	~SphereBoundaryCoordinator(void){};

	virtual void coordinate(const ParticleVector& particles);

private:
	const float radius;
	const Math::Vector3d center;
};
*/

	}
}


#endif