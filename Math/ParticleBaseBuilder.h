#ifndef __CRYSTAL_MATH_PARTICLE_BASE_BUILDER_H__
#define __CRYSTAL_MATH_PARTICLE_BASE_BUILDER_H__

#include <list>

#include "ParticleBase.h"

namespace Crystal {
	namespace Math {

		class ParticleBaseBuilder : private UnCopyable {
		public:
			ParticleBaseBuilder() :
				nextId(0)
			{}

			ParticleBaseBuilder(const float diameter) :
				divideLength(diameter),
				nextId(0)
			{}

			std::list<ParticleBaseSPtr> create(const Box& box);

			std::list<ParticleBaseSPtr> create(const Sphere& sphere);

			std::list<ParticleBaseSPtr> create(const Cylinder& cylinder);

		private:
			float divideLength;
			unsigned int nextId;
		};

	}
}

#endif