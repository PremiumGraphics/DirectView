#include "gtest/gtest.h"

#include "../Physics/PhysicsParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(NeighborSearchAlgoTest, Test)
{
	const auto particle1 = std::make_shared<PhysicsParticle>(Vector3d(0.0, 0.0, 0.0));
	const auto particle2 = std::make_shared<PhysicsParticle>(Vector3d(1.0, 0.0, 0.0));
	const PhysicsParticleSPtrVector particles{
		particle1,
		particle2,
	};

	{
		PhysicsParticleFindAlgo algo;
		algo.createPairs(particles, 1.1f);
		const auto& pairs = algo.getPairs();
		EXPECT_EQ(2, pairs.size());
	}

	{
		PhysicsParticleFindAlgo algo;
		algo.createPairs(particles, 0.9f);
		const auto& pairs = algo.getPairs();
		EXPECT_TRUE( pairs.empty());
	}
}