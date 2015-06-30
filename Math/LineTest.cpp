#include "gtest/gtest.h"

#include "Line.h"

using namespace Crystal::Math;

template<class T>
class LineTest : public testing::Test {
};

typedef ::testing::Types<float> TestTypes;

TYPED_TEST_CASE(LineTest, TestTypes);


TYPED_TEST(LineTest, TestGet)
{
	using T = TypeParam;

	const Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	EXPECT_EQ( Vector3d<T>(0, 0, 0), line.getStart());
	EXPECT_EQ( Vector3d<T>(0.5, 2.5, 5), line.getCenter());
	EXPECT_EQ( Vector3d<T>(1, 5, 10), line.getEnd());
}

TYPED_TEST(LineTest, TestGetPosition)
{
	using T = TypeParam;
	const Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	EXPECT_EQ(Vector3d<T>(0,0,0), line.getPosition(0));
	EXPECT_EQ(Vector3d<T>(0.5, 2.5, 5), line.getPosition(0.5));

}
//T getLength() const { vector.getLength(); }
