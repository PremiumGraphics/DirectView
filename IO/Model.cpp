#include "Model.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

ParticleObjectSPtr Model::getObjectById(const unsigned int id)
{
	for (const ParticleObjectSPtr& object : objects) {
		if (object->getId() == id) {
			return object;
		}
	}
	return nullptr;
}
