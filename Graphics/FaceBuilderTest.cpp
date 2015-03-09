#include "gtest/gtest.h"

#include "FaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(FaceBuilderTest, TestBuildQuad)
{
	VertexBuilder vBuilder;
	FaceBuilder builder(vBuilder);
	builder.buildQuad();
	const FaceVector& faces = builder.getFaces();
	EXPECT_EQ(1, faces.size());
	EXPECT_EQ(0, faces.front()->getId());
}

TEST(FaceBuilderTest, TestBuildCirlceByNumber)
{
	VertexBuilder vBuilder;
	FaceBuilder builder(vBuilder);
	builder.buildCircleByNumber( 3, 3);
	const FaceVector& faces = builder.getFaces();
	EXPECT_EQ(1, faces.size());
	EXPECT_EQ(0, faces.front()->getId());
}

TEST(FaceBuilderTest, TestBuildCirleByAngle)
{

}