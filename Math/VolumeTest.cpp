#include "gtest/gtest.h"

#include "../Math/Volume.h"
#include "Density.h"

#include <tuple>

using namespace Crystal::Math;

template<class T>
class Volume3dTest : public testing::Test {
};

//using GeomTypes = ::testing::Types < float > ;
using ValueTypes = ::testing::Types < unsigned char > ;

TYPED_TEST_CASE(Volume3dTest, ValueTypes);

TYPED_TEST(Volume3dTest, TestGetStart)
{
	using GeomType = float;
	using ValueType = TypeParam;
	Volume3d<GeomType> gs;
	EXPECT_EQ(Vector3d<GeomType>(0, 0, 0), gs.getStart());
}

TYPED_TEST(Volume3dTest, TestToCells)
{
	using GeomType = float;
	using ValueType = TypeParam;
	EXPECT_EQ(1, Volume3d<GeomType>(Space3d<GeomType>::Unit(), Grid3d<GeomType>(2, 2, 2)).toCells().size());
}

TYPED_TEST(Volume3dTest, TestGetOverlapped)
{
	using GeomType = float;
	using ValueType = TypeParam;
	Volume3d<GeomType> ss(Space3d<GeomType>(Vector3d<GeomType>(0, 0, 0), Vector3d<GeomType>(2, 2, 2)), Grid3d<GeomType>(2, 2, 2));
	const auto actual = ss.getOverlapped(Space3d<GeomType>(Vector3d<GeomType>(1, 1, 1), Vector3d<GeomType>(2, 2, 2)));
	EXPECT_EQ(Grid3d<GeomType>(1, 1, 1), actual.getGrid());

	//BitSpace3d<GeomType> lhs(Space3d<GeomType>(Vector3d<GeomType>(0, 0, 0), Vector3d<GeomType>(2, 2, 2)), Bitmap3d(2, 2, 2));
	//BitSpace3d<GeomType> rhs(Space3d<GeomType>(Vector3d<GeomType>(1, 1, 1), Vector3d<GeomType>(2, 2, 2)), Bitmap3d(2, 2, 2));
	//EXPECT_EQ(Bitmap3d(1, 1, 1), lhs.getOverlapped(rhs).getBitmap());
}

TYPED_TEST(Volume3dTest, TestAdd)
{
	using GeomType = float;
	using ValueType = TypeParam;
	Volume3d<GeomType, ValueType> lhs(Space3d<GeomType>(Vector3d<GeomType>(0, 0, 0), Vector3d<GeomType>(2, 2, 2)), Grid3d<ValueType>(2, 2, 2));
	Volume3d<GeomType, ValueType> rhs(Space3d<GeomType>(Vector3d<GeomType>(1, 1, 1), Vector3d<GeomType>(2, 2, 2)), Grid3d<ValueType>(2, 2, 2));
	lhs.add(rhs);
}