#include "gtest/gtest.h"
/*
#include "ParticleTopology.h"

using namespace Crystal::Particle;

TEST(ParticleTopologyTest, TestConstruct)
{
	const ParticleTopology t;
	EXPECT_EQ(nullptr, t.getCenter());
	EXPECT_EQ(nullptr, t.getUplus());
	EXPECT_EQ(nullptr, t.getUminus());
	EXPECT_EQ(nullptr, t.getVplus());
	EXPECT_EQ(nullptr, t.getVminus());
	EXPECT_EQ(nullptr, t.getWplus());
	EXPECT_EQ(nullptr, t.getWplus());
}

TEST(ParticleTopologyTest, TestConstructByOneParticle)
{
	const auto center = std::make_shared<ParticleBase>();
	const ParticleTopology t( center );
	EXPECT_EQ(center, t.getCenter());

	EXPECT_EQ(nullptr, t.getUplus());
	EXPECT_EQ(nullptr, t.getUminus());
	EXPECT_EQ(nullptr, t.getVplus());
	EXPECT_EQ(nullptr, t.getVminus());
	EXPECT_EQ(nullptr, t.getWplus());
	EXPECT_EQ(nullptr, t.getWplus());
}

TEST(ParticleTopologyTest, TestGetSet)
{
	ParticleTopology t;
	const auto center = std::make_shared<ParticleBase>();
	const auto uplus = std::make_shared<ParticleBase>();
	const auto vplus = std::make_shared<ParticleBase>();
	const auto wplus = std::make_shared<ParticleBase>();

	const auto uminus = std::make_shared<ParticleBase>();
	const auto vminus = std::make_shared<ParticleBase>();
	const auto wminus = std::make_shared<ParticleBase>();

	t.setUplus(uplus);
	t.setVplus(vplus);
	t.setWplus(wplus);

	t.setUMinus(uminus);
	t.setVMinus(vminus);
	t.setWMinus(wminus);

	EXPECT_EQ(uplus, t.getUplus());
	EXPECT_EQ(vplus, t.getVplus());
	EXPECT_EQ(wplus, t.getWplus());

	EXPECT_EQ(uminus, t.getUminus());
	EXPECT_EQ(vminus, t.getVminus());
	EXPECT_EQ(wminus, t.getWminus());
}
*/