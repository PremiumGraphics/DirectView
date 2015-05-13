#include "gtest/gtest.h"
#include "../Math/Ellipse.h"

using namespace Crystal::Math;

template<class T>
class EllipseTest : public testing::Test {
};

typedef ::testing::Types<float> TestTypes;

TYPED_TEST_CASE(EllipseTest, TestTypes);

TYPED_TEST(EllipseTest, TestGetXRadius)
{
	using T = TypeParam;
	EXPECT_EQ( 1.0f, Ellipse<T>().getXRadius());
	EXPECT_EQ( 1.0f, Ellipse<T>(1.0f, 2.0f).getXRadius());
	EXPECT_EQ( 2.0f, Ellipse<T>(2.0f, 4.0f).getXRadius());
}

TYPED_TEST(EllipseTest, TestGetYRadius)
{
	using T = TypeParam;
	EXPECT_EQ( 1.0f, Ellipse<T>().getYRadius() );
	EXPECT_EQ( 2.0f, Ellipse<T>(1.0f, 2.0f).getYRadius() );
	EXPECT_EQ( 4.0f, Ellipse<T>(2.0f, 4.0f).getYRadius() );
}

TYPED_TEST(EllipseTest, TestGetMajor)
{
	using T = TypeParam;
	EXPECT_EQ(1.0f, Ellipse<T>().getMajor());
	EXPECT_EQ(2.0f, Ellipse<T>(1.0f, 2.0f).getMajor());

}

TYPED_TEST(EllipseTest, TestIsCircle)
{
	using T = TypeParam;
	EXPECT_TRUE (Ellipse<T>().isCircle());
	EXPECT_FALSE(Ellipse<T>(1.0f, 2.0f).isCircle());
	EXPECT_TRUE (Ellipse<T>(2.0f, 2.0f).isCircle());
}

TYPED_TEST(EllipseTest, TestGetArea)
{
	using T = TypeParam;
	EXPECT_FLOAT_EQ( Tolerances::getPI(), Ellipse<T>(1.0f, 1.0f).getArea() );
	EXPECT_FLOAT_EQ( Tolerances::getTwoPI(), Ellipse<T>(2.0f, 1.0f).getArea());
}

TYPED_TEST(EllipseTest, TestIsShrinked)
{
	using T = TypeParam;
	EXPECT_FALSE( Ellipse<T>().isShrinked() );
	EXPECT_TRUE ( Ellipse<T>(0.0f, 0.0f).isShrinked() );

}