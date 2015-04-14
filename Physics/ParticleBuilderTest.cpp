#include <gtest/gtest.h>
#include "ParticleBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(ParticleBaseTest, TestGetVolume)
{
	ParticleBase particle(1.0f, Vector3d( 0.0f, 0.0f, 0.0f) );
	EXPECT_FLOAT_EQ( 1.0f, particle.getVolume() );
}

TEST(ParticleBuilderTest, TestBuildBox)
{
	ParticleBuilder builder(1.0f);
	const Box b(Vector3d( 0.0, 0.0, 0.0 ), Vector3d( 10.0f, 1.0f, 1.0f ));
	const std::list<ParticleBase>& actual = builder.build(b.getInnerOffset( 0.5f ));
	EXPECT_EQ(10, actual.size());
}

/*
TEST(ParticleBuilderTest, TestBuildCircle)
{
	ParticleBuilder builder(1.0f);
	..const Circle c()
	builder.build()
}
*/