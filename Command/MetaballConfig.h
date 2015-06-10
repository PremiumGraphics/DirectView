#ifndef __CRYSTAL_COMMAND_METABALL_CONFIG_H__
#define __CRYSTAL_COMMAND_METABALL_CONFIG_H__

#include "../Math/Vector.h"

namespace Crystal {
	namespace Command {

class MetaballConfig
{
public:
	MetaballConfig() :
		radius(1),
		charge(1)
	{}

	~MetaballConfig() = default;

	MetaballConfig(const Math::Vector3d<float>& center, const float radius, const float charge) :
		center( center ),
		radius( radius ),
		charge( charge )
	{
	}

	Math::Vector3d<float> getCenter() const { return center; }

	float getRadius() const { return radius; }

	float getCharge() const { return charge; }

private:
	Math::Vector3d<float> center;
	float radius;
	float charge;
};
	}
}

#endif