#ifndef __CRYSTAL_MATH_PARTICLE_BASE_BUILDER_H__
#define __CRYSTAL_MATH_PARTICLE_BASE_BUILDER_H__

#include "ParticleBase.h"

namespace Crystal {
	namespace Math {

		class ParticleBuilder : private UnCopyable {
		public:
			ParticleBuilder() :
				nextId(0)
			{}

			ParticleBuilder(const float diameter) :
				divideLength(diameter),
				nextId(0)
			{}

			std::vector<ParticleBaseSPtr> create(const Box& box);

			std::vector<ParticleBaseSPtr> create(const Sphere& sphere);

			std::vector<ParticleBaseSPtr> create(const Cylinder& cylinder);

		private:
			float divideLength;
			unsigned int nextId;
		};

	}
}

#endif