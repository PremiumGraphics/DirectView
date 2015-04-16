#ifndef __CRYSTAL_GRAPHICS_SURFACE_BUILDER_H__
#define __CRYSTAL_GRAPHICS_SURFACE_BUILDER_H__

#include "../Physics/ParticleObject.h"
#include "Polygon.h"

namespace Crystal {
	namespace Graphics {

class SurfaceBuilder {
public:
	Polygon* build(const Physics::ParticleObject& object);

private:
};
	}
}

#endif