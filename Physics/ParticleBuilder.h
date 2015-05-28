#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "Particle.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Physics {

template<typename T>
class ParticleBuilder final : private UnCopyable {
public:
	ParticleBuilder() :
		nextId(0),
		divideLength( 1.0f )
	{}

	~ParticleBuilder() = default;

	unsigned int getNextId() const { return nextId; }

	float getDivideLength() const { return divideLength; }

	ParticleSPtrVector create(const Math::Box<T>& box) {
		ParticleSPtrVector particles;
		for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
			for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
				for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
					particles.push_back(std::make_shared<Particle<T> >(constant, Math::Vector3d<T>(x, y, z)));
					//object->add(p);
				}
			}
		}
		return particles;
	}

	ParticleSPtrVector create(const Math::Sphere<float>& sphere) {
		Math::Box<float> box = sphere.getBoundingBox();
		Math::Vector3dVector<float> positions;
		for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
			for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
				for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
					const Math::Vector3d<float> v(x, y, z);
					if (sphere.isInner(v)) {
						positions.push_back(v);
					}
				}
			}
		}
		return create(positions);
	}

	ParticleSPtrVector create(const Math::Cylinder<T>& cylinder) {
		const Math::Box<float>& box = cylinder.getBoundingBox();
		Math::Vector3dVector<float> positions;
		for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
			for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
				for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
					const Math::Vector3d<float> v(x, y, z);
					if (cylinder.isInner(v)) {
						positions.push_back(v);
					}
				}
			}
		}
		return create(positions);
	}

	ParticleSPtrVector create(const Math::Vector3dVector<T>& positions) {
		ParticleSPtrVector particles;
		for (const auto& p : positions) {
			particles.push_back(std::make_shared<Particle<T> >(constant, p));
		}
		return particles;
	}

private:
	unsigned int nextId;
	T divideLength;
	Particle<float>::Constant constant;
};

	}
}

#endif