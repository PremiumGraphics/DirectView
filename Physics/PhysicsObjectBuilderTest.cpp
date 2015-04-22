#include "gtest/gtest.h"

#include "../Math/Box.h"

#include "PhysicsObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(PhysicsObjectBuilderTest, TestBuildBox)
{
	PhysicsObjectBuilder builder;
	const Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const PhysicsObjectSPtr& object = builder.create(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, object->getParticles().size());
}