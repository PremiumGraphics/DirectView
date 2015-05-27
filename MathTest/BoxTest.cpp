#include "gtest/gtest.h"
 
#include "../Math/Box.h"

using namespace Crystal::Math;
 
template<class T>
class BoxTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(BoxTest, TestTypes);

TYPED_TEST( BoxTest, TestGetMin )
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0.0f, 0.0f, 0.0f), Box_<T>().getMin() );
	EXPECT_EQ( Vector3d<T>(1.0f, 2.0f, 3.0f), Box_<T>( Vector3d<T>(1.0f, 2.0f, 3.0f), Vector3d<T>(4.0f, 5.0f, 6.0f)).getMin());
}

TYPED_TEST(BoxTest, TestGetMax)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>(1.0f, 1.0f, 1.0f), Box_<T>().getMax());
	EXPECT_EQ(Vector3d<T>(4.0f, 5.0f, 6.0f), Box_<T>(Vector3d<T>(1.0f, 2.0f, 3.0f), Vector3d<T>(4.0f, 5.0f, 6.0f)).getMax());
}

TYPED_TEST( BoxTest, TestGetVolume )
{
	using T = TypeParam;
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(6.0f, Box_<T>(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(1.0f, 2.0f, 3.0f)).getVolume()));
}

TYPED_TEST( BoxTest, TestGetLength )
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0.0, 1.0, 2.0), Box_<T>(Vector3d<T>(1.0f, 1.0f, 1.0f), Vector3d<T>(1.0f, 2.0f, 3.0f)).getLength());
}

TYPED_TEST( BoxTest, TestOuterOffset )
{
	using T = TypeParam;
	EXPECT_EQ(Box_<T>(Vector3d<T>(-1.0f, -1.0f, -1.0f), Vector3d<T>(2.0f, 2.0f, 2.0f)), Box_<T>().getOuterOffset(1.0f));
}

TYPED_TEST( BoxTest, TestIsShrinked )
{
	using T = TypeParam;

	EXPECT_TRUE(Box_<T>(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(0.0f, 0.0f, 0.0f)).isShirinked());
	EXPECT_FALSE(Box_<T>(Vector3d<T>(0.0f, 0.0, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f)).isShirinked());
}

TYPED_TEST( BoxTest, TestIsValid )
{
	using T = TypeParam;

	EXPECT_TRUE(Box_<T>(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(0.0f, 0.0f, 0.0f)).isValid());
	EXPECT_TRUE(Box_<T>(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f)).isValid());
}

TYPED_TEST(BoxTest, TestHasIntersection)
{
	using T = TypeParam;

	Box_<T> b1(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f));
	Box_<T> b2(Vector3d<T>(2.0f, 2.0f, 2.0f), Vector3d<T>(4.0f, 4.0f, 4.0f));

	EXPECT_FALSE(b1.hasIntersection(b2));
}

TYPED_TEST(BoxTest, TestGetOverlapped)
{
	using T = TypeParam;

	Box_<T> b1(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f));
	Box_<T> b2(Vector3d<T>(0.5f, 0.5f, 0.5f), Vector3d<T>(2.0f, 2.0f, 2.0f));
	const Box_<T> expected(Vector3d<T>(0.5f, 0.5f, 0.5f), Vector3d<T>(1.0f, 1.0f, 1.0f));
	const auto actual = b1.getOverlapped(b2);
	EXPECT_EQ(expected, actual);
}