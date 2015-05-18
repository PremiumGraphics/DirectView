#include <gtest/gtest.h>

#include "../Particle/ParticleBasePair.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleBasePairTest, TestConstruct)
{
	ParticleBasePair pair;
	EXPECT_EQ( nullptr, pair.getParticle1() );
	EXPECT_EQ( nullptr, pair.getParticle2() );
	EXPECT_FALSE(pair.isValid());
}

TEST(ParticleBasePairTest, TestConstructByTwoParticles)
{
	const auto particle1 = std::make_shared<ParticleBase>();
	const auto particle2 = std::make_shared<ParticleBase>();
	const ParticleBasePair pair( particle1, particle2 );
	EXPECT_TRUE( pair.isValid() );
}

TEST(ParticleBasePairTest, TestGetDistance)
{
	const auto particle1 = std::make_shared<ParticleBase>( Vector3d( 0.0, 0.0, 0.0 ) );
	const auto particle2 = std::make_shared<ParticleBase>( Vector3d( 1.0, 0.0, 0.0 ) );
	const ParticleBasePair pair(particle1, particle2);
	EXPECT_FLOAT_EQ( 1.0f, pair.getDistance() );
}

TEST(ParticleBasePairTest, TestIsNeighbor)
{
	const auto particle1 = std::make_shared<ParticleBase>(Vector3d(0.0, 0.0, 0.0));
	const auto particle2 = std::make_shared<ParticleBase>(Vector3d(1.0, 0.0, 0.0));
	const ParticleBasePair pair(particle1, particle2);
	EXPECT_FALSE( pair.isNeighbor() );

	particle1->setPosition(Vector3d(0.5f, 0.0, 0.0));
	EXPECT_TRUE(pair.isNeighbor());
}