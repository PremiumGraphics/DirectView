#ifndef __CRYSTAL_PARTICLE_PARTICLE_OBJECT_BUILDER_H__
#define __CRYSTAL_PARTICLE_PARTICLE_OBJECT_BUILDER_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

#include "ParticleBase.h"
#include "ParticleObject.h"

#include "../Util/UnCopyable.h"

#include <list>

namespace Crystal {
	namespace Particle {

class ParticleObjectBuilder : private UnCopyable {
public:
	ParticleObjectBuilder() :
		divideLength( 1.0f ),
		density(1.0f),
		nextId(0)
	{}

	ParticleObjectBuilder(const float divideLength) :
		divideLength(divideLength),
		density(1.0f),
		nextId(0)
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

	//std::list<ParticleObject*> getObjects() const { return objects; }

	ParticleObjectSPtr build(const std::list<ParticleBaseSPtr>& particles);

	ParticleObjectSPtr getObject(const unsigned int id);

	float getDivideLength() const { return divideLength; }

	float getDensity() const { return density; }

	unsigned int getNextId() const { return nextId; }

private:
	float divideLength;
	float density;
	//std::list<ParticleObject*> objects;
	unsigned int nextId;

};

	}
}

#endif