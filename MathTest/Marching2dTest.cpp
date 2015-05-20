#include "gtest/gtest.h"

#include "../Math/Marching2d.h"

using namespace Crystal::Math;

TEST(Marching2dTest, Test)
{
	Marching2d<float> march;
	march.march(Space2x2<float>());
}