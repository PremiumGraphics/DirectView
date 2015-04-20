#include "gtest/gtest.h"

#include "ParticleObject.h"

#include "ParticleObjectBuilder.h"

using namespace Crystal::Math;

TEST(ParticleObjectTest, TestAdd)
{
	ParticleObject object(0);
	ParticleBaseSPtr particle = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(particle);
	EXPECT_EQ(1, object.getParticles().size());
}

TEST(ParticleObjectTest, TestRemove)
{
	ParticleObject object(0);
	ParticleBaseSPtr particle = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(particle);
	EXPECT_EQ(1, object.getParticles().size());
	ParticleBaseSPtr particle1 = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	object.remove(particle1);
	EXPECT_TRUE(object.getParticles().empty());
}

TEST(ParticleObjectTest, TestSub)
{
	ParticleObject object(0);
	ParticleBaseSPtr particle = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(particle);
	EXPECT_EQ(1, object.getParticles().size());
	ParticleBaseSPtr particle1 = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	ParticleObject rhs(1);
	rhs.add(particle1);
	object.sub(rhs);
	EXPECT_TRUE(object.getParticles().empty());
}

TEST(ParticleObjectTest, TestIsInner)
{
	ParticleObject object(0);
	ParticleBaseSPtr particle = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(particle);
	EXPECT_EQ(1, object.getParticles().size());

	ParticleBase rhs(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	EXPECT_TRUE(object.isInner(&rhs));

	ParticleBase far(1.0f, Vector3d(10.0f, 0.0f, 0.0f), 2);
	EXPECT_FALSE(object.isInner(&far));
}

TEST(ParticleObjectTest, TestIsOuter)
{
	ParticleObject object(0);
	ParticleBaseSPtr particle = std::make_shared<ParticleBase>(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 0);
	object.add(particle);
	EXPECT_EQ(1, object.getParticles().size());

	ParticleBase rhs(1.0f, Vector3d(0.0f, 0.0f, 0.0f), 1);
	EXPECT_FALSE(object.isOuter(&rhs));

	ParticleBase far(1.0f, Vector3d(10.0f, 0.0f, 0.0f), 2);
	EXPECT_TRUE(object.isOuter(&far));
}

TEST(ParticleObjectTest, TestGetBoundingBox)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr object = builder.build(b);
	const Box actual = object->getBoundingBox();
	EXPECT_EQ(object->getBoundingBox(), b);
}

TEST(ParticleObjectTest, TestToPositionArray)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr object = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(30, object->toPositionArray().size());
}

TEST(ParticleObjectTest, TestToIdArray)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr object = builder.build(b.getInnerOffset(0.5f));
	EXPECT_EQ(10, object->toIdArray().size());
}

TEST(ParticleBooleanAlgoTest, TestCreateUnion)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr lhs = builder.build(b1.getInnerOffset(0.5f));

	const Box b2(Vector3d(10.0f, 0.0f, 0.0f), Vector3d(20.0f, 1.0f, 1.0f));
	ParticleObjectSPtr rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const std::list<ParticleBaseSPtr> actual = algo.createUnion(*lhs, *rhs);
	EXPECT_EQ(20, actual.size());

}

TEST(ParticleBooleanAlgoTest, TestCreateIntersection)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr lhs = builder.build(b1.getInnerOffset( 0.5f));

	const Box b2(Vector3d(1.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const std::list<ParticleBaseSPtr> actual = algo.createIntersection(*lhs, *rhs);
	EXPECT_EQ(9, actual.size());
}


TEST(ParticleBooleanAlgoTest, TestCreateDiff)
{
	ParticleObjectBuilder builder(1.0f);
	const Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr lhs = builder.build(b1.getInnerOffset(0.5f));

	const Box b2(Vector3d(1.0f, 0.0f, 0.0f), Vector3d(10.0f, 1.0f, 1.0f));
	ParticleObjectSPtr rhs = builder.build(b2.getInnerOffset(0.5f));

	ParticleBooleanAlgo algo;
	const std::list<ParticleBaseSPtr> actual = algo.createDiff(*lhs, *rhs);
	EXPECT_EQ(1, actual.size());
}