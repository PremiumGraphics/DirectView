#include <gtest/gtest.h>

#include "ParticleBasePair.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleBasePairTest, TestConstruct)
{
	ParticleBasePair pair;
	EXPECT_FALSE(pair.isValid());
}

TEST(ParticleBasePairTest, TestGetDistance)
{
	ParticleBaseSPtr particle1 = std::make_shared<ParticleBase>();
	particle1->setPosition(Vector3d(0.0, 0.0, 0.0));
	ParticleBaseSPtr particle2 = std::make_shared<ParticleBase>();
	particle2->setPosition(Vector3d(1.0, 0.0, 0.0));
	ParticleBasePair pair(particle1, particle2);
	EXPECT_FLOAT_EQ( 1.0f, pair.getDistance() );
}