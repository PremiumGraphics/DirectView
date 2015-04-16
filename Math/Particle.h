#ifndef __CRYSTAL_MATH_PARTICLE_H__
#define __CRYSTAL_MATH_PARTICLE_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class ParticleBase {
public:
	ParticleBase(const float diameter, const Math::Vector3d& position, const unsigned int id) :
		diameter(diameter),
		position(position),
		id(id)
	{}

	Math::Vector3d getPosition() const { return position; }

	float getVolume() const { return diameter * diameter * diameter; }

	unsigned int getId() const { return id; }

private:
	float diameter;
	Math::Vector3d position;
	unsigned int id;
};
	}
}

#endif

