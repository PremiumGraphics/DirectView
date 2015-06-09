#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_TRANSFORM_COMMAND_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_TRANSFORM_COMMAND_H__

#include "../Math/ScalarSpace.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Command {

class ScalarSpaceTransformCommand final
{
public:
	void clear() {
		spaces.clear();
	}

	//Math::ScalarSpace3dSPtr<float> getSelected() { return  }

	bool isEmpty() const { return spaces.empty(); }

private:
	Math::ScalarSpace3dSPtrList<float> spaces;
};

using ScalarSpaceTransformCommandSPtr = std::shared_ptr < ScalarSpaceTransformCommand > ;

	}
}


#endif