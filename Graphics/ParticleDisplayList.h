#ifndef __CRYSTAL_GRAPHICS_PARTICLE_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_PARTICLE_DISPLAY_LIST_H__

#include <vector>

#include "../Particle/ParticleObject.h"
#include "ColorRGB.h"

namespace Crystal {
	namespace Graphics {

class ParticleDisplayList
{
public:
	void add(const Math::ParticleObject& object );

	void add(const Math::ParticleObject& object, const ColorRGB<float>& color);

	void clear() {
		positions.clear();
		colors.clear();
	}

	std::vector<float> getPositions() const { return positions; }

	std::vector<float> getColors() const { return colors; }

	ColorRGB<float> toColor(const Math::ParticleBase& particle);

	std::vector< ColorRGB<float> > toColors(const Math::ParticleObject& object);
	
private:
	std::vector<float> positions;
	std::vector<float> colors;
};
	}
}

#endif