#ifndef __CRYSTAL_GRAPHICS_PARTICLE_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_PARTICLE_DISPLAY_LIST_H__

#include <vector>

#include "../Math/ParticleObject.h"

namespace Crystal {
	namespace Graphics {

class ParticleDisplayList
{
public:
	void add(const Math::ParticleObject& object);

	void clear() {
		positions.clear();
		ids.clear();
	}

	std::vector<float> getPositions() const { return positions; }

	std::vector<unsigned int> getIds() const { return ids; }

private:
	std::vector<float> positions;
	std::vector<unsigned int> ids;
};
	}
}

#endif