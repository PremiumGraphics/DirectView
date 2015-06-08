#ifndef __CRYSTAL_COMMAND_SPACE_PICK_COMMAND_H__
#define __CRYSTAL_COMMAND_SPACE_PICK_COMMAND_H__

#include "../Math/ScalarSpace.h"
#include "ScalarSpaceFactory.h"

#include <list>

namespace Crystal {
	namespace CGS {

class SpacePickCommand
{
public:
	void clear() {
		selecteds.clear();
	}

	//Math::ScalarSpace3dSPtr<float> getSelected() { return  }

	bool isEmpty() const { return selecteds.empty(); }

private:
	Math::ScalarSpace3dSPtrList<float> selecteds;
	ScalarSpaceFactory factory;
};
	}
}

#endif