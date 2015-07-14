#include "gtest/gtest.h"

#include "../Math/MarchingCube.h"

using namespace Crystal::Math;

template<class T>
class MarchingCubeTest : public testing::Test {
};

using TestTypes = ::testing::Types <
	std::tuple< float, float >//,
//	std::tuple< float, unsigned char >
>;


TYPED_TEST_CASE(MarchingCubeTest, TestTypes);

//
//TEST(MarchingCubeTest, TestMarchFloats)
//{
//	MarchingCube<float> mc;
//	mc.buildTable();
//
//	Space3d<float> s(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));
//
//	const std::array< float, 8 > vs = { 0, 0, 0, 0, 1, 1, 1, 1 };
//	const auto actual = mc.build( s, vs,0.5).getTriangles();
//	EXPECT_EQ(2, actual.size());
//
//	{
//		const auto actual = mc.build(s, { 0, 0, 0, 0, 0, 0, 0, 0 }, 0.5);
//		EXPECT_EQ(0, actual.size());
//	}
//
//	{
//		const auto actual = mc.build(s, { 1, 0, 0, 0, 0, 0, 0, 0 },0.5);
//		EXPECT_EQ(1, actual.size());
//	}
//
//	{
//		const auto actual = mc.build(s, { 1, 1, 0, 0, 0, 0, 0, 0 }, 0.5);
//		EXPECT_EQ(2, actual.size());
//	}
//
//	/*
//	{
//		const auto actual = mc.Polygonise(p, { 1, 0, 1, 0, 0, 1, 0, 0 }, 0.5);
//		EXPECT_EQ(2, actual.size());
//	}
//	*/
//
//	{
//		const auto actual = mc.build(s, { 1, 0, 0, 0, 0, 0, 1, 0 }, 0.5);
//		EXPECT_EQ(2, actual.size());
//	}
//
//	/*
//	{
//		const auto actual = mc.Polygonise(p, { 0, 1, 0, 1, 0, 0, 1, 0 }, 0.5);
//		EXPECT_EQ(3, actual.size());
//	}
//	*/
//
//
//	{
//		const auto actual = mc.build(s, { 1, 0, 0, 1, 0, 1, 1, 0 }, 0.5);
//		EXPECT_EQ(4, actual.size());
//	}
//
//
//	{
//		const auto actual = mc.build(s, { 1, 1, 1, 1, 1, 1, 1, 1 }, 0.5);
//		EXPECT_EQ(0, actual.size());
//	}
//
//}



TYPED_TEST(MarchingCubeTest, TestMarchScalarSpace)
{
	using GeomType = std::tuple_element<0, TypeParam>::type;
	using ValueType = std::tuple_element<1, TypeParam>::type;


	MarchingCube<GeomType, ValueType> mc;

	Space3d<GeomType> s(Vector3d<GeomType>(0, 0, 0), Vector3d<GeomType>(10, 10, 10));
	const Grid3d<ValueType> grid(2,2,2);
	Volume3d<GeomType, ValueType> ss(s, grid);

	mc.march(ss, 1);
}