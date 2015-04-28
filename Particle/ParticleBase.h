#ifndef __CRYSTAL_PARTICLE_PARTICLE_BASE_H__
#define __CRYSTAL_PARTICLE_PARTICLE_BASE_H__

#include "../Util/UnCopyable.h"

#include "../Math/Vector3d.h"

#include <memory>
#include <list>

namespace Crystal {
	namespace Math {
		class Box;
	}
	namespace Particle {

class ParticleBase : private UnCopyable {
public:
	ParticleBase() : ParticleBase(1.0f) {}

	ParticleBase(const float diameter) : ParticleBase(diameter, Math::Vector3d(0.0, 0.0, 0.0), 1.0f, -1) {}

	ParticleBase(const Math::Vector3d& position) : ParticleBase( 1.0f, position, -1) {}

	ParticleBase(const float diameter, const Math::Vector3d& position, const unsigned int id) : ParticleBase( diameter, position, 1.0f, id ) {}

	ParticleBase(const float diameter, const Math::Vector3d& position, const float density, const unsigned int id);

	virtual ~ParticleBase() = default;

	float getRadius() const { return diameter * 0.5f; }

	float getDiameter() const { return diameter; }

	Math::Vector3d getPosition() const { return position; }

	void setPosition(const Math::Vector3d& p) { this->position = p; }

	float getDensity() const { return density; }

	float getVolume() const { return diameter * diameter * diameter; }

	float getMass() const { return getDensity() * getVolume(); }

	unsigned int getId() const { return id; }

	Math::Box toBox() const;


private:
	float diameter;
	float density;
	Math::Vector3d position;
	unsigned int id;
};

using ParticleBaseSPtr = std::shared_ptr < ParticleBase >;
using ParticleBaseSPtrList = std::list < ParticleBaseSPtr >;

	}
}

#endif