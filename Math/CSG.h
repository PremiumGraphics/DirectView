#ifndef __CRYSTAL_MATH_CSG_H__
#define __CRYSTAL_MATH_CSG_H__

#include <list>

#include "Primitive.h"

namespace Crystal {
	namespace Math {

class CSG {
public:

private:
	std::list<Primitive*> primitive;
};

	}
}

#endif