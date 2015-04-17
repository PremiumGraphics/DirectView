#include "gtest/gtest.h"

#include "ParticleObject.h"

#include "ParticleBuilder.h"

using namespace Crystal::Math;

TEST(ParticleObjectTest, TestAdd)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());
}

TEST(ParticleObjectTest, TestRemove)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());
	ParticleBase particle1(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	object.remove(&particle1);
	EXPECT_TRUE(object.getParticles().empty());
}

TEST(ParticleObjectTest, TestSub)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());
	ParticleBase particle1(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	ParticleObject rhs;
	rhs.add(&particle1);
	object.sub(rhs);
	EXPECT_TRUE(object.getParticles().empty());
}

TEST(ParticleObjectTest, TestIsInner)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());

	ParticleBase rhs(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	EXPECT_TRUE(object.isInner(&rhs));

	ParticleBase far(1.0f, Vector3d(10.0f, 0.0f, 0.0f), 2);
	EXPECT_FALSE(object.isInner(&far));
}

TEST(ParticleObjectTest, TestIsOuter)
{
	ParticleObject object;
	ParticleBase particle(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(&particle);
	EXPECT_EQ(1, object.getParticles().size());

	ParticleBase rhs(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	EXPECT_FALSE(object.isOuter(&rhs));

	ParticleBase far(1.0f, Vector3d(10.0f, 0.0f, 0.0f), 2);
	EXPECT_TRUE(object.isOuter(&far));
}

TEST(ParticleObjectTest, TestGetBoundingBox)
{
	ParticleBuilder builder(1.0f);
	const Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const ParticleObject& object = builder.build(b);
	EXPECT_EQ(object.getBoundingBox(), b);
}

TEST(ParticleObjectTest, TestCreateUnion)
{
	ParticleBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const ParticleObject& lhs = builder.build(b1.getInnerOffset(0.5f));

	const Box b2(Vector3d(10.0f, 0.0f, 0.0f), Vector3d(20.0f, 1.0f, 1.0f));
	const ParticleObject& rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const std::list<ParticleBase*> actual = algo.createUnion(lhs, rhs);
	EXPECT_EQ(20, actual.size());

}

TEST(ParticleBooleanAlgoTest, TestIntersection)
{
	ParticleBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const ParticleObject& lhs = builder.build(b1.getInnerOffset( 0.5f));

	const Box b2(Vector3d(1.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	const ParticleObject& rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const std::list<ParticleBase*> actual = algo.createIntersection(lhs, rhs);
	EXPECT_EQ(9, actual.size());
}