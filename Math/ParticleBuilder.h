#ifndef __CRYSTAL_MATH_PARTICLE_BUILDER_H__
#define __CRYSTAL_MATH_PARTICLE_BUILDER_H__

#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"

#include "ParticleBase.h"
#include "ParticleObject.h"

#include "../Util/UnCopyable.h"

#include <list>

namespace Crystal {
	namespace Math {


/*
class ParticleBooleanAlgo {

};
*/

class ParticleBuilder : private UnCopyable {
public:
	ParticleBuilder(const float divideLength) :
		divideLength(divideLength),
		nextId(0)
	{}

	~ParticleBuilder() {
		clear();
	}

	void clear();

	ParticleObject* build(const Math::Box& box);

	ParticleObject* build(const Math::Sphere& s);

	ParticleObject* build(const Math::Cylinder& c);

	std::list<ParticleBase*> getParticles() const { return particles; }

	std::list<ParticleObject*> getObjects() const { return objects; }

private:
	float divideLength;
	std::list<ParticleBase*> particles;
	std::list<ParticleObject*> objects;
	unsigned int nextId;
};
	}
}

#endif