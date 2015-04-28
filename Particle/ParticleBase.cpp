#include "ParticleBase.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

ParticleBase::ParticleBase(const float diameter, const Vector3d& position, const float density, const unsigned int id) :
diameter(diameter),
position(position),
density(density),
id(id)
{}

Box ParticleBase::toBox() const
{	
	const auto minx = position.getX() - getRadius();
	const auto miny = position.getY() - getRadius();
	const auto minz = position.getZ() - getRadius();

	const auto maxx = position.getX() + getRadius();
	const auto maxy = position.getY() + getRadius();
	const auto maxz = position.getZ() + getRadius();

	return Box(Vector3d(minx, miny, minz), Vector3d(maxx, maxy, maxz));
}
