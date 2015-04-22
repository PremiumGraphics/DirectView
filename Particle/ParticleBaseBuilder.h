#ifndef __CRYSTAL_PARTICLE_PARTICLE_BASE_BUILDER_H__
#define __CRYSTAL_PARTICLE_PARTICLE_BASE_BUILDER_H__

#include <list>

#include "ParticleBase.h"

namespace Crystal {
	namespace Particle {

class ParticleBaseBuilder : private UnCopyable {
public:
	ParticleBaseBuilder() :
		nextId(0),
		density(1.0f)
	{}

	ParticleBaseBuilder(const float diameter) :
		divideLength(diameter),
		density(1.0f),
		nextId(0)
	{}

	float getDivideLength() const { return divideLength; }

	float getDensity() const { return density; }

	void setDivideLength(const float l) { this->divideLength = l; }

	void setDensity(const float d) { this->density = density; }

	std::list<ParticleBaseSPtr> create(const Math::Box& box);

	std::list<ParticleBaseSPtr> create(const Math::Sphere& sphere);

	std::list<ParticleBaseSPtr> create(const Math::Cylinder& cylinder);

private:
	float divideLength;
	float density;
	unsigned int nextId;
};

	}
}

#endif