#include "gtest/gtest.h"

#include "Model.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(ModelTest, TestConstruct)
{
	Model model;
	EXPECT_TRUE( model.getParticleObjects().empty() );
	EXPECT_TRUE( model.getSelectedObjects().empty() );
}

TEST(ModelTest, TestCreate)
{
	Model model;
	model.create();
	EXPECT_EQ(1, model.getParticleObjects().size());
}

TEST(ModelTest, TestCreateBox)
{
	Model model;
	Box b;
	model.create(b);
	EXPECT_EQ(1, model.getParticleObjects().size());
}

TEST(ModelTest, TestCreateCylinder)
{
	Model model;
	Cylinder c;
	model.create(c);
	EXPECT_EQ(1, model.getParticleObjects().size());
}

TEST(ModelTest, TestClearObjects)
{
	Model model;
	model.create();
	EXPECT_EQ(1, model.getParticleObjects().size());
	model.clearObjects();
	EXPECT_TRUE(model.getParticleObjects().empty());
}

TEST(ModelTest, TestFindObjectById)
{
	Model model;
	const ParticleObjectSPtr& lhs = model.create();
	const ParticleObjectSPtr& rhs = model.getObjectById(0);
	EXPECT_EQ(lhs, rhs);
}