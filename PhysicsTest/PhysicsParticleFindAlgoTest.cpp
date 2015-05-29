#include "gtest/gtest.h"

#include "../Physics/PhysicsParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST(NeighborSearchAlgoTest, Test)
{
	const auto particle1 = std::make_shared<Particle<T> >(Vector3d<T>(0.0, 0.0, 0.0));
	const auto particle2 = std::make_shared<Particle<T> >(Vector3d<T>(1.0, 0.0, 0.0));
	const ParticleSPtrVector particles{
		particle1,
		particle2,
	};

	{
		ParticleFindAlgo algo;
		algo.createPairs(particles, 1.1f);
		const auto& pairs = algo.getPairs();
		EXPECT_EQ(2, pairs.size());
	}

	{
		ParticleFindAlgo algo;
		algo.createPairs(particles, 0.9f);
		const auto& pairs = algo.getPairs();
		EXPECT_TRUE( pairs.empty());
	}
}