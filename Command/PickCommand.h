#ifndef __CRYSTAL_COMMAND_PICK_COMMAND_H__
#define __CRYSTAL_COMMAND_PICK_COMMAND_H__

#include "ScalarSpaceFactory.h"
#include "MetaballFactory.h"

#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Command {

enum class PickType {
	ScalarSpace = 0,
	Metaball = 1,
	Light = 2,	
	Polygon = 3,
};

template<typename T>
class PickCommand{
public:
	PickCommand() = default;

	PickCommand(const ScalarSpaceFactorySPtr<T>& ssFactory, const MetaballFactorySPtr<T>& ballFactory ):
		ssFactory( ssFactory ),
		ballFactory( ballFactory )
	{}

	Math::ScalarSpace3dSPtr<T> find(const int id) {
		if (ssFactory == nullptr) {
			return nullptr;
		}
		return ssFactory->find(id);
	}
	//fromPickType(const int type, const int id) {
	//}

private:
	ScalarSpaceFactorySPtr<T> ssFactory;
	MetaballFactorySPtr<T> ballFactory;
};
	}
}

#endif