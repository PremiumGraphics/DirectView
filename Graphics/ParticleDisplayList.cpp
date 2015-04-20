#include "ParticleDisplayList.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void ParticleDisplayList::add(const ParticleObject& object)
{
	const std::vector< float >& ps = object.toPositionArray();
	positions.insert(positions.end(), ps.begin(), ps.end() );

	const std::vector<unsigned int>& is = object.toIdArray();
	ids.insert(ids.end(), is.begin(), is.end());

	std::vector<unsigned int> objectIds_(object.getParticles().size(), object.getId());
	this->objectIds.insert(objectIds.end(), objectIds_.begin(), objectIds_.end());
}
