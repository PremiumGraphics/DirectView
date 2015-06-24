#include "gtest/gtest.h"

#include "Particle.h"

using namespace Crystal::Math;

TEST(MetaballTest, TestGetRadius)
{
	using T = float;
	EXPECT_EQ(1, Particle3d<T>().getRadius());
	EXPECT_EQ(10, Particle3d<T>(Vector3d<T>(0, 0, 0), 10, 1).getRadius());
}

TEST(MetaballTest, TestGetCenter)
{
	using T = float;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Particle3d<T>().getCenter());

}