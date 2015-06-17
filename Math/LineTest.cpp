#include "gtest/gtest.h"

#include "Line.h"

using namespace Crystal::Math;

template<class T>
class LineTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(LineTest, TestTypes);


TYPED_TEST(LineTest, TestGet)
{
	using T = TypeParam;

	Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	EXPECT_EQ( Vector3d<T>(0, 0, 0), line.getStart());
	EXPECT_EQ( Vector3d<T>(1, 1, 1), line.getEnd());
}