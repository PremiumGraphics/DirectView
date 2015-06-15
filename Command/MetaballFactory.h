#ifndef __CRYSTAL_COMMAND_METABALL_FACTORY_H__
#define __CRYSTAL_COMMAND_METABALL_FACTORY_H__

#include <list>
#include <memory>

#include "../Math/Kernel.h"
#include "../Util/UnCopyable.h"

#include "MainConfig.h"

#include "Object.h"
#include "Factory.h"

namespace Crystal {
	namespace Command {

template<typename T>
class MetaballObject final : public Object
{
public:
	MetaballObject(const Math::MetaballSPtr<T>& metaball, const unsigned int id) :
		Object( id ),
		metaball(metaball)
	{}

	Math::MetaballSPtr<T> getMetaball() const { return metaball; }

private:
	Math::MetaballSPtr<T> metaball;
};

template<typename T>
using MetaballObjectList = std::list < MetaballObject<T> > ;

template<typename T>
class MetaballObjectFactory final : public ObjectFactory, private UnCopyable
{
public:
	MetaballObjectFactory()
	{

	}

	~MetaballObjectFactory() = default;

	MetaballObjectFactory& clear() {
		ObjectFactory::clear();
		balls.clear();
		return (*this);
	}

	MetaballObject<T> create(const MetaballConfig<T>& config) {
		const auto& center = config.getCenter();
		const auto radius = config.getRadius();
		const auto charge = config.getCharge();
		const auto metaball = std::make_shared<Math::Metaball<T> >(center, radius, charge);
		return add(metaball);
	}

	MetaballObjectList<T> getBalls() const { return balls; }

	MetaballObject<T> find(const unsigned int id) {
		for (const auto& b : balls) {
			if (b.getId() == id) {
				return b.getMetaball();
			}
		}
		return nullptr;
	}


private:
	MetaballObjectList<T> balls;

	MetaballObject<T> add(const Math::MetaballSPtr<T>& ball) {
		balls.push_back(MetaballObject<T>(ball, getNextId()));
		return balls.back();
	}

};

template<typename T>
using MetaballFactorySPtr = std::shared_ptr < MetaballObjectFactory<T> > ;
	}
}

#endif