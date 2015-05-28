#ifndef __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__

#include "Coordinator.h"

#include "../Math/Box.h"
#include "../Math/Vector.h"

#include <vector>

namespace Crystal{
	namespace Physics{

template<typename T>
class BoundaryCoordinator : public Coordinator
{
public:
	BoundaryCoordinator(const Math::Box<T>& box, const T timeStep ) :
		box( box ),
		timeStep( timeStep )
	{}

	~BoundaryCoordinator(void){};

	virtual void coordinate(const ParticleSPtrVector& particles) {
		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
			particles[i]->addForce(getForce(particles[i]->getCenter() ) * particles[i]->getDensity());
		}
	}

private:
	const Math::Box<T> box;
	const T timeStep;

	Math::Vector3d<T> getForce(const Math::Vector3d<T>& center) {
		Math::Vector3d<T> force = Math::Vector3d<T>::Zero();

		force += getForceX(center.getX() );
		force += getForceY(center.getY() );
		force += getForceZ(center.getZ() );

		return force;

	}

	Math::Vector3d<T> getForceX(const T x)
	{
		T over = 0.0f;
		if (x > box.getMaxX()) {
			over = x - box.getMaxX();
		}
		else if (x < box.getMinX()) {
			over = x - box.getMinX();
		}

		const float force = getForce(over);
		return Math::Vector3d<T>::UnitX() * force;
	}

	Math::Vector3d<float> getForceY(const float y)
	{
		T over = 0.0f;
		if (y > box.getMaxY()) {
			over = y - box.getMaxY();
		}
		else if (y < box.getMinY()) {
			over = y - box.getMinY();
		}
		const float force = getForce(over);
		return Math::Vector3d<T>::UnitY() * force;
	}

	Math::Vector3d<T> getForceZ(const float z)
	{
		T over = 0.0f;
		if (z > box.getMaxZ()) {
			over = z - box.getMaxZ();
		}
		else if (z < box.getMinZ()) {
			over = z - box.getMinZ();
		}
		const T force = getForce(over);
		return Math::Vector3d<T>::UnitZ() * force;

	}

	T getForce(const T over) {
		return -over / timeStep / timeStep;
	}


};

	}
}


#endif