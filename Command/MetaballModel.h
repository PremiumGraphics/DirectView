#ifndef __CRYSTAL_COMMAND_METABALL_MODEL_H__
#define __CRYSTAL_COMMAND_METABALL_MODEL_H__

#include <list>
#include <memory>

#include "../Math/Kernel.h"

#include "Object.h"

namespace Crystal {
	namespace Model {

template<typename T>
class MetaballConfig {
public:
	MetaballConfig()
	{
		setDefault();
	}

	MetaballConfig(const Math::Vector3d<T>& center, const T radius, const T charge) :
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
class MetaballObject final : public Object
{
public:
	MetaballObject(const Math::MetaballSPtr<T>& metaball, const unsigned int id) :
		Object( id ),
		metaball(metaball)
	{}

	Type getType() const { return Type::Metaball; }


	Math::MetaballSPtr<T> getMetaball() const { return metaball; }

	virtual void move(const Math::Vector3d<float>& vector) override
	{
		metaball->move(vector);
	};

	virtual void rotate(const Math::Vector3d<float>& center, const Math::Vector3d<float>& angle) override
	{
		;
	};


private:
	Math::MetaballSPtr<T> metaball;
};

template<typename T>
using MetaballObjectSPtr = std::shared_ptr < MetaballObject<T> > ;

template<typename T>
using MetaballObjectSPtrList = std::list < MetaballObjectSPtr<T> > ;

template<typename T>
class MetaballModel final : public ModelBase
{
public:
	MetaballModel()
	{

	}

	~MetaballModel() = default;

	MetaballModel& clear() {
		ModelBase::clear();
		balls.clear();
		return (*this);
	}

	MetaballObjectSPtr<T> create() {
		const auto& center = config.getCenter();
		const auto radius = config.getRadius();
		const auto charge = config.getCharge();
		const auto metaball = std::make_shared<Math::Metaball<T> >(center, radius, charge);
		return add(metaball);
	}

	MetaballObjectSPtrList<T> getBalls() const { return balls; }

	MetaballObjectSPtr<T> find(const unsigned int id) {
		for (const auto& b : balls) {
			if (b->getId() == id) {
				return b;
			}
		}
		return nullptr;
	}

	void remove(const unsigned int id) override {
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

	MetaballConfig<T> getConfig() const { return config; }

	void setConfig(const MetaballConfig<T>& config) { this->config = config; }


private:
	MetaballObjectSPtrList<T> balls;

	MetaballObjectSPtr<T> add(const Math::MetaballSPtr<T>& ball) {
		balls.push_back( std::make_shared< MetaballObject<T> >(ball, getNextId()));
		return balls.back();
	}

	MetaballConfig<T> config;

};

template<typename T>
using MetaballModelSPtr = std::shared_ptr < MetaballModel<T> > ;
	}
}

#endif