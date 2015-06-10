#ifndef __CRYSTAL_COMMAND_METABALL_FACTORY_H__
#define __CRYSTAL_COMMAND_METABALL_FACTORY_H__

#include <list>

#include "../Math/Kernel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

template<typename T>
class MetaballFactory final : private UnCopyable
{
public:
	MetaballFactory() = default;

	~MetaballFactory() = default;

	Math::MetaballSPtrList<T> getBalls() const { return balls; }

private:
	Math::MetaballSPtrList<T> balls;
};
	}
}

#endif