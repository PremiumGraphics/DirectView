#include "gtest/gtest.h"

#include "../Physics/PhysicsParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST(PhysicsParticlePairTest, TestConstruct)
{
	const PhysicsParticlePair<T> pair;
	EXPECT_EQ(nullptr, pair.getParticle1());
	EXPECT_EQ(nullptr, pair.getParticle2());
	EXPECT_FALSE(pair.isValid());
}

TEST(PhysicsParticlePairTest, TestConstructByTwoParticles)
{
	const auto p1 = std::make_shared< PhysicsParticle<T> >();
	const auto p2 = std::make_shared< PhysicsParticle<T> >();
	const PhysicsParticlePair<T> pair(p1, p2);

	EXPECT_EQ(p1, pair.getParticle1());
	EXPECT_EQ(p2, pair.getParticle2());
	EXPECT_TRUE(pair.isValid());
}

TEST(PhysicsParticlePairTest, TestIsValid)
{
	const auto p = std::make_shared< PhysicsParticle<T> >();
	const PhysicsParticlePair<T> pair(p, p);
	EXPECT_FALSE(pair.isValid());
}

TEST(PhysicsParticlePairTest, TestGetDistanceSquared)
{
	const auto p1 = std::make_shared< PhysicsParticle<T> >( Vector3d<T>( 0.0f, 0.0f, 0.0f ));
	const auto p2 = std::make_shared< PhysicsParticle<T> >( Vector3d<T>( 1.0f, 1.0f, 1.0f ));

	const PhysicsParticlePair<T> pair(p1, p2);
	EXPECT_FLOAT_EQ(3.0f, pair.getDistanceSquared());
}

TEST(PhysicsParticlePairTest, TestGetDistance)
{
	const auto p1 = std::make_shared< PhysicsParticle<T> >(Vector3d<T>(0.0f, 0.0f, 0.0f));
	const auto p2 = std::make_shared< PhysicsParticle<T> >(Vector3d<T>(1.0f, 1.0f, 1.0f));

	const PhysicsParticlePair<T> pair(p1, p2);
	EXPECT_FLOAT_EQ( std::sqrt( 3.0f ), pair.getDistance());
}

TEST(PhysicsParticlePairTest, TestGetDistanceVector)
{
	const auto p1 = std::make_shared< PhysicsParticle<T> >(Vector3d<T>(1.0f, 2.0f, 3.0f));
	const auto p2 = std::make_shared< PhysicsParticle<T> >(Vector3d<T>(0.0f, 0.0f, 0.0f));

	const PhysicsParticlePair<T> pair(p1, p2);
	const auto actual = pair.getDistanceVector();
	const auto expected = Vector3d<T>(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(actual, expected);
}