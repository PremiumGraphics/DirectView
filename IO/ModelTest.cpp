#include "gtest/gtest.h"

#include "Model.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(ModelTest, Test)
{
	Model model;
	Box b(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0, 1.0, 1.0));
	model.getParticleBuilder().build(b);
}