#ifndef __CRYSTAL_COMMAND_METABALL_CONFIG_H__
#define __CRYSTAL_COMMAND_METABALL_CONFIG_H__

#include "../Math/Vector.h"

namespace Crystal {
	namespace Command {

class MetaballConfig
{
public:
	MetaballConfig(const Math::Vector3d<float>& center, const float radius) :
		center( center ),
		radius( radius )
	{
	}

	Math::Vector3d<float> getCenter() const { return center; }

	float getRadius() const { return radius; }

private:
	Math::Vector3d<float> center;
	float radius;
};
	}
}

#endif