#include "PhysicsParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float PhysicsParticle::getDensityRatio() const
{
	return density / constant.getRestDensity();
}

float PhysicsParticle::getPressure() const
{
	return constant.pressureCoe * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float PhysicsParticle::getMass() const
{
	return constant.getRestDensity() * std::pow(constant.getDiameter(), 3);
}