#include "gtest/gtest.h"

#include "../Particle/ParticleBooleanAlgo.h"
#include "../Particle/ParticleObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

TEST(ParticleBooleanAlgoTest, TestCreateUnion)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const auto& lhs = builder.build(b1.getInnerOffset(0.5f));

	const Box b2(Vector3d(10.0f, 0.0f, 0.0f), Vector3d(20.0f, 1.0f, 1.0f));
	const auto& rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const ParticleBaseSPtrList& actual = algo.createUnion(*lhs, *rhs);
	EXPECT_EQ(20, actual.size());

}

TEST(ParticleBooleanAlgoTest, TestCreateIntersection)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const auto& lhs = builder.build(b1.getInnerOffset(0.5f));

	const Box b2(Vector3d(1.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const auto& rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const ParticleBaseSPtrList& actual = algo.createIntersection(*lhs, *rhs);
	EXPECT_EQ(9, actual.size());
}


TEST(ParticleBooleanAlgoTest, TestCreateDiff)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const auto& lhs = builder.build(b1.getInnerOffset(0.5f));

	const Box b2(Vector3d(1.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const auto& rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const ParticleBaseSPtrList& actual = algo.createDiff(*lhs, *rhs);
	EXPECT_EQ(1, actual.size());
}