#ifndef __CRYSTAL_CGS_SPACE_PICK_COMMAND_H__
#define __CRYSTAL_CGS_SPACE_PICK_COMMAND_H__

#include "../Math/ScalarSpace.h"
#include "SpaceFactory.h"

#include <list>

namespace Crystal {
	namespace CGS {

class SpacePickCommand
{
public:
	void clear() {
		spaces.clear();
	}

	//Math::ScalarSpace3dSPtr<float> getSelected() { return  }

	bool isEmpty() const { return spaces.empty(); }

private:
	Math::ScalarSpace3dSPtrList<float> selecteds;
	Math::ScalarSpace3dSPtrList<float> spaces;
};
	}
}

#endif