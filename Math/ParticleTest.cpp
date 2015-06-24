#include "gtest/gtest.h"

#include "Particle.h"

using namespace Crystal::Math;

TEST(ParticleTest, TestGet)
{
	using T = float;
	EXPECT_EQ(1, Particle3d<T>().getRadius());
	EXPECT_EQ(2, Particle3d<T>().getDiameter());

	EXPECT_EQ(10, Particle3d<T>(Vector3d<T>(0, 0, 0), 10, 1).getRadius());
	EXPECT_EQ(20, Particle3d<T>(Vector3d<T>(0, 0, 0), 10, 1).getDiameter());
}

TEST(ParticleTest, TestGetCenter)
{
	using T = float;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Particle3d<T>().getCenter());
}

TEST(ParticleTest, TestGetSpace)
{
	using T = float;
	Space3d<T> expected(Vector3d<T>(-1,-1,-1), Vector3d<T>(2,2,2));
	EXPECT_EQ( expected,Particle3d<T>().getSpace());
}