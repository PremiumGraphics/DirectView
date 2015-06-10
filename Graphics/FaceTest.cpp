#include "gtest/gtest.h"

#include "Face.h"

using namespace Crystal::Graphics;

TEST(FaceTest, TestIsLine)
{
	Face<float> f;
	f.add(std::make_shared<HalfEdge<float> >());
	f.isLine();
}