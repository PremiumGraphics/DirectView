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
class MetaballFactory final : private UnCopyable
{
public:
	MetaballFactory() = default;

	~MetaballFactory() = default;

	MetaballFactory& clear() {
		balls.clear();
		return (*this);
	}

	MetaballFactory& add(const Math::MetaballSPtr<T>& ball) {
		balls.push_back(ball);
		return (*this);
	}

	Math::MetaballSPtr<T> create(const MetaballConfig<T>& config) {
		const auto& center = config.getCenter();
		const auto radius = config.getRadius();
		const auto charge = config.getCharge();
		const auto metaball = std::make_shared<Metaball<T> >(center, radius, charge);
		add(metaball);
		return metaball;
	}

	Math::MetaballSPtrList<T> getBalls() const { return balls; }

private:
	Math::MetaballSPtrList<T> balls;
};

using MetaballFactorySPtr = std::shared_ptr < MetaballFactory<float> > ;
	}
}

#endif