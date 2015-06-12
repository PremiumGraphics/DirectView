#ifndef __CRYSTAL_COMMAND_METABALL_FACTORY_H__
#define __CRYSTAL_COMMAND_METABALL_FACTORY_H__

#include <list>
#include <memory>

#include "../Math/Kernel.h"

#include "../Util/UnCopyable.h"

#include "MainConfig.h"

namespace Crystal {
	namespace Command {

template<typename T>
class MetaballId
{
public:
	MetaballId(const Math::MetaballSPtr<T>& metaball, const unsigned int id) :
		metaball(metaball),
		id(id)
	{}

	Math::MetaballSPtr<T> getMetaball() const { return metaball; }

	unsigned int getId() const { return id; }

private:
	Math::MetaballSPtr<T> metaball;
	unsigned int id;
};

template<typename T>
using MetaballIdList = std::list < MetaballId<T> > ;

template<typename T>
class MetaballFactory final : private UnCopyable
{
public:
	MetaballFactory() :
		nextId(0)
	{

	}

	~MetaballFactory() = default;

	MetaballFactory& clear() {
		balls.clear();
		nextId = 0;
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

	unsigned int getNextId() const { return nextId; }

private:
	MetaballIdList<T> balls;
	unsigned int nextId;

	MetaballId<T> add(const Math::MetaballSPtr<T>& ball) {
		balls.push_back(MetaballId<T>(ball, nextId++));
		return balls.back();
	}

};

using MetaballFactorySPtr = std::shared_ptr < MetaballFactory<float> > ;
	}
}

#endif