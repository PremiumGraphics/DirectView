#ifndef __CRYSTAL_COMMAND_PARTICLE_MODEL_H__
#define __CRYSTAL_COMMAND_PARTICLE_MODEL_H__

#include <list>
#include <memory>

#include "../Math/Kernel.h"

namespace Crystal {
	namespace Model {

template<typename T>
class ParticleConfig {
public:
	ParticleConfig()
	{
		setDefault();
	}

	ParticleConfig(const Math::Vector3d<T>& center, const T radius, const T charge) :
		center(center),
		radius(radius),
		charge(charge)
	{}

	void setDefault() {
		center = Math::Vector3d<T>(0, 0, 0);
		radius = 1;
		charge = 1;
	}

	Math::Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	T getCharge() const { return charge; }

private:
	Math::Vector3d<T> center;
	T radius;
	T charge;
};

template<typename T>
class ParticleObject final : private UnCopyable
{
public:
	ParticleObject(const Math::MetaballSPtr<T>& metaball, const unsigned int id) :
		id( id ),
		metaball(metaball),
		selected(true)
	{}

	int getType() const { return 2; }

	unsigned int getId() const { return id; }

	bool isSelected() const { return selected; }

	void setSelect() { selected = true; }

	void setUnSelect() { selected = false; }

	void changeSelected() { selected = !selected; }


	Math::MetaballSPtr<T> getMetaball() const { return metaball; }

	void move(const Math::Vector3d<float>& vector)
	{
		metaball->move(vector);
	};


private:
	Math::MetaballSPtr<T> metaball;
	unsigned int id;
	bool selected;
};

template<typename T>
using ParticleObjectSPtr = std::shared_ptr < ParticleObject<T> > ;

template<typename T>
using ParticleObjectSPtrList = std::list < ParticleObjectSPtr<T> > ;


template<typename T>
class ParticleModel final : private UnCopyable
{
public:
	ParticleModel() :
		nextId(0)
	{

	}

	~ParticleModel() = default;

	ParticleModel& clear() {
		nextId = 0;
		balls.clear();
		return (*this);
	}

	ParticleObjectSPtr<T> create() {
		const auto& center = config.getCenter();
		const auto radius = config.getRadius();
		const auto charge = config.getCharge();
		const auto metaball = std::make_shared<Math::Particle3d<T> >(center, radius, charge);
		return add(metaball);
	}

	ParticleObjectSPtrList<T> getParticles() const { return balls; }

	ParticleObjectSPtr<T> find(const unsigned int id) {
		for (const auto& b : balls) {
			if (b->getId() == id) {
				return b;
			}
		}
		return nullptr;
	}

	void remove(const unsigned int id)  {
		const auto& b = find(id);
		if (b == nullptr) {
			return;
		}
		balls.remove(b);
	}

	void move(const Math::Vector3d<T>& vector) {
		for (const auto& b : balls) {
			if (b->isSelected()) {
				b->move(vector);
			}
		}
	}

	void deleteSelected() {
		for (auto iter = balls.begin(); iter != balls.end(); ) {
			const auto ball = (*iter);
			if (ball->isSelected()) {
				iter = balls.erase(iter);
				continue;
			}
			++iter;
		}
	}

	void clearSelected() {
		for (auto& b : balls) {
			b->setUnSelect();
		}
	}

	ParticleConfig<T> getConfig() const { return config; }

	void setConfig(const ParticleConfig<T>& config) { this->config = config; }


private:
	ParticleObjectSPtrList<T> balls;

	ParticleObjectSPtr<T> add(const Math::MetaballSPtr<T>& ball) {
		balls.push_back( std::make_shared< ParticleObject<T> >(ball, nextId++));
		return balls.back();
	}

	ParticleConfig<T> config;
	unsigned int nextId;
};

template<typename T>
using ParticleModelSPtr = std::shared_ptr < ParticleModel<T> > ;
	}
}

#endif