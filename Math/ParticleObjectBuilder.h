#ifndef __CRYSTAL_MATH_PARTICLE_OBJECT_BUILDER_H__
#define __CRYSTAL_MATH_PARTICLE_OBJECT_BUILDER_H__

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

class ParticleObjectBuilder : private UnCopyable {
public:
	ParticleObjectBuilder(const float divideLength) :
		divideLength(divideLength),
		nextId(0),
		nextObjectId(0)
	{}

	~ParticleObjectBuilder() {
		clear();
	}

	void clear();

	ParticleObjectSPtr build();

	//ParticleObject* build(const std::list<ParticleBase*> particles);

	ParticleObjectSPtr build(const Math::Box& box);

	ParticleObjectSPtr build(const Math::Sphere& s);

	ParticleObjectSPtr build(const Math::Cylinder& c);

	std::list<ParticleBase*> getParticles() const { return particles; }

	//std::list<ParticleObject*> getObjects() const { return objects; }

	ParticleObjectSPtr getObject(const unsigned int id);

private:
	float divideLength;
	std::list<ParticleBase*> particles;
	//std::list<ParticleObject*> objects;
	unsigned int nextId;
	unsigned int nextObjectId;

};

	}
}

#endif