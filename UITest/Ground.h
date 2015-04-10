#ifndef __CRYSTAL_MODELING_GROUND_H__
#define __CRYSTAL_MODELING_GROUND_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Modeling {

class Ground {
public:
	Ground(unsigned int divX, unsigned int divY) :
		divideX( divX ),
		divideY( divY )
	{}

	unsigned int getDivideX() const { return divideX; }

	unsigned int getDivideY() const { return divideY; }

private:
	unsigned int divideX;
	unsigned int divideY;

};
	}
}

#endif