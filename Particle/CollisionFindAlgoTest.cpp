#include "gtest/gtest.h"

#include "ParticleFindAlgo.h"
#include "ParticleBaseBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(CollisionFindAlgoTest, TestGetPairs)
{
	ParticleFindAlgo algo;
	ParticleBaseBuilder builder(1.0f);
	Box box(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0, 1.0, 1.0));
	const std::list<ParticleBaseSPtr>& particles = builder.create(box.getInnerOffset(0.5f));
	const std::vector<ParticleBasePair>& pairs = algo.getPairs(particles);
	EXPECT_TRUE(pairs.empty());
}