#ifndef __CRYSTAL_COMMAND_PICK_COMMAND_H__
#define __CRYSTAL_COMMAND_PICK_COMMAND_H__

#include "ScalarSpaceFactory.h"
#include "MetaballFactory.h"

#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Command {


template<typename T>
class PickCommand{
public:
	PickCommand() = default;

	PickCommand(const ScalarSpaceFactorySPtr<T>& ssFactory, const MetaballFactorySPtr<T>& ballFactory ):
		ssFactory( ssFactory ),
		ballFactory( ballFactory )
	{}

	Object* find(const int id) {
		if (ssFactory == nullptr) {
			return NullObject();
		}
		const auto ptr = ssFactory->find(id);
		if (ptr != nullptr) {
			return ptr;
		}
		//const auto ptr2 = ballFactory->find()
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