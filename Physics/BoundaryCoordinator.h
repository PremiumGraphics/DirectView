#ifndef __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__

#include "Coordinator.h"

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

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

	virtual void coordinate(const PhysicsParticleSPtrVector& particles) {
		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
			particles[i]->addForce(getForce(particles[i]->getCenter(), box) * particles[i]->getDensity());
		}
	}

private:
	const Math::Box<float> box;
	const float timeStep;

	Math::Vector3d<float> getForce(const Math::Vector3d<float>& center, const Math::Box<float>& box) {
		Math::Vector3d<float> force = Math::Vector3d<float>::Zero();

		force += getForceX(center.getX(), box );
		force += getForceY(center.getY(), box );
		force += getForceZ(center.getZ(), box, timeStep);

		return force;

	}

	Math::Vector3d<float> getForceX(const float x, const Math::Box<float>& box)
	{
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

	Math::Vector3d<float> getForceY(const float y, const Math::Box<float>& box)
	{
		float over = 0.0f;
		if (y > box.getMaxY()) {
			over = y - box.getMaxY();
		}
		else if (y < box.getMinY()) {
			over = y - box.getMinY();
		}
		const float force = getForce(over);
		return Math::Vector3d<float>::UnitY() * force;

	}

	Math::Vector3d<float> getForceZ(const float z, const Math::Box<float>& box, const float timeStep)
	{
		float over = 0.0f;
		if (z > box.getMaxZ()) {
			over = z - box.getMaxZ();
		}
		else if (z < box.getMinZ()) {
			over = z - box.getMinZ();
		}
		const float force = getForce(over);
		return Math::Vector3d<float>::UnitZ() * force;

	}

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