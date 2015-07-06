#ifndef __CRYSTAL_ACTOR_ACTOR_H__
#define __CRYSTAL_ACTOR_ACTOR_H__

#include "Bone.h"

#include <list>

namespace Crystal {
	namespace Actor {

template<typename T>
class Actor {
	std::list< Joint<T> > joints;
};


	}
}

#endif