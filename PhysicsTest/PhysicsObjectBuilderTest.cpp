#include "gtest/gtest.h"

#include "../Math/Box.h"

#include "../Physics/PhysicsObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST(PhysicsObjectBuilderTest, TestBuildBox)
{
	PhysicsObjectBuilder builder;
	const Box<T> b(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(10.0f, 1.0f, 1.0f));
	const PhysicsObjectSPtr& object = builder.create(b.getInnerOffset(0.5f), PhysicsObject::Type::Fluid );
	EXPECT_EQ(10, object->getParticles().size());
}