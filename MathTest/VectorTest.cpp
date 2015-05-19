#include "gtest/gtest.h"
#include "../Math/Vector.h"

using namespace Crystal::Math;

template<class T>
class VectorTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;
//typedef ::testing::Types<1, 2> TestDims;

TYPED_TEST_CASE(VectorTest, TestTypes);


TYPED_TEST(VectorTest, TestGetSet)
{
	using T = TypeParam;
	Vector<T, 1> v;
	EXPECT_EQ( 0.0, v.get<0>());
}