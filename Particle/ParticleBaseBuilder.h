#ifndef __CRYSTAL_PARTICLE_PARTICLE_BASE_BUILDER_H__
#define __CRYSTAL_PARTICLE_PARTICLE_BASE_BUILDER_H__

#include <list>

#include "ParticleBase.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

namespace Crystal {
	namespace Particle {

class ParticleBaseBuilder : private UnCopyable {
public:
	ParticleBaseBuilder() : ParticleBaseBuilder( 1.0f ) {}

	ParticleBaseBuilder(const float diameter) :
		divideLength(diameter),
		density(1.0f),
		nextId(0)
	{}

	float getDivideLength() const { return divideLength; }

	float getDensity() const { return density; }

	void create(const Math::Box& box);

	void create(const Math::Sphere& sphere);

	void create(const Math::Cylinder& cylinder);

	ParticleBaseSPtrList getParticles() const { return particles; }

private:
	float divideLength;
	float density;
	unsigned int nextId;
	ParticleBaseSPtrList particles;
	std::vector< ParticleBaseSPtr > slicez;
};

	}
}

#endif