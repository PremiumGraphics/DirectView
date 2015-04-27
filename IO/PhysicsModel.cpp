#include "PhysicsModel.h"

#include "../Math/Box.h"
#include "../Math/Cylinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::IO;

PhysicsObjectSPtr PhysicsModel::create(const Box& box)
{
	const PhysicsObjectSPtr& object = builder.create(box, PhysicsObject::Type::Fluid);
	objects.push_back(object);
	return object;
}

/*
PhysicsObjectSPtr PhysicsModel::create(const Cylinder& c)
{
	const PhysicsObjectSPtr& object = builder.create(c);
	objects.push_back(object);
	return object;
}
*/