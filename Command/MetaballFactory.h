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
class MetaballId final : public Object
{
public:
	MetaballId(const Math::MetaballSPtr<T>& metaball, const unsigned int id) :
		Object( id ),
		metaball(metaball)
	{}

	Math::MetaballSPtr<T> getMetaball() const { return metaball; }

private:
	Math::MetaballSPtr<T> metaball;
};

template<typename T>
using MetaballIdList = std::list < MetaballId<T> > ;

template<typename T>
class MetaballFactory final : public FactoryBase, private UnCopyable
{
public:
	MetaballFactory()
	{

	}

	~MetaballFactory() = default;

	MetaballFactory& clear() {
		FactoryBase::clear();
		balls.clear();
		return (*this);
	}

	MetaballId<T> create(const MetaballConfig<T>& config) {
		const auto& center = config.getCenter();
		const auto radius = config.getRadius();
		const auto charge = config.getCharge();
		const auto metaball = std::make_shared<Math::Metaball<T> >(center, radius, charge);
		return add(metaball);
	}

	MetaballIdList<T> getBalls() const { return balls; }

	MetaballId<T> find(const unsigned int id) {
		for (const auto& b : balls) {
			if (b.getId() == id) {
				return b.getMetaball();
			}
		}
		return nullptr;
	}


private:
	MetaballIdList<T> balls;

	MetaballId<T> add(const Math::MetaballSPtr<T>& ball) {
		balls.push_back(MetaballId<T>(ball, getNextId()));
		return balls.back();
	}

};

template<typename T>
using MetaballFactorySPtr = std::shared_ptr < MetaballFactory<T> > ;
	}
}

#endif