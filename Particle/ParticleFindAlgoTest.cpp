#include "gtest/gtest.h"

#include "ParticleFindAlgo.h"
#include "ParticleBaseBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;


TEST(ParticleFindAlgoTest, TestGetPairs)
{
	ParticleFindAlgo algo;
	ParticleBaseBuilder builder(1.0f);
	Box box(Vector3d(0.0, 0.0, 0.0), Vector3d(10.0, 1.0, 1.0));
	builder.create(box.getInnerOffset(0.5f));
	const auto& particles = builder.getParticles();
	const ParticleBasePairVector& pairs = algo.findPairs(particles);
	EXPECT_TRUE(pairs.empty());
}

TEST(ParticleFindAlgoTest, TestFindMap)
{
	ParticleFindAlgo algo;
	const auto p1 = std::make_shared<ParticleBase>(Vector3d(0.0, 0.0, 0.0));
	const auto p2 = std::make_shared<ParticleBase>(Vector3d(0.5f, 0.0f, 0.0f));
	const std::list<ParticleBaseSPtr> particles{ p1, p2 };
	const auto& map = algo.buildMap(particles);
	auto iter = map.find(p1);
	EXPECT_TRUE(iter != map.end());
	EXPECT_EQ( p1, iter->first );
	EXPECT_EQ( p2, iter->second );
	iter = map.find(p2);
	EXPECT_TRUE(iter != map.end());
	EXPECT_EQ(p2, iter->first);
	EXPECT_EQ(p1, iter->second );
}