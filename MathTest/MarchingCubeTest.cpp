#include "gtest/gtest.h"

#include "../Math/MarchingCube.h"

using namespace Crystal::Math;

TEST(MarchingCubeTest, TestBuild)
{
	MarchingCube<float> mc;
	mc.buildTable();
	//mc.Polygonise( )
	const Vector3d<float> v1(0, 0, 0 );
	const Vector3d<float> v2(10, 10, 10);
	const Vector3d<float> actual = mc.interpolate(0.5, v1, v2, 0.0, 1.0);
	EXPECT_EQ( Vector3d<float>({ 5, 5, 5 }), actual);
}

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
//	EXPECT_EQ(2, actual.getTriangles().size());
//
//	{
//		const auto actual = mc.build(s, { 0, 0, 0, 0, 0, 0, 0, 0 }, 0.5);
//		EXPECT_EQ(0, actual.getTriangles().size());
//	}
//
//	{
//		const auto actual = mc.build(s, { 1, 0, 0, 0, 0, 0, 0, 0 },0.5);
//		EXPECT_EQ(1, actual.getTriangles().size());
//	}
//
//	{
//		const auto actual = mc.build(s, { 1, 1, 0, 0, 0, 0, 0, 0 }, 0.5);
//		EXPECT_EQ(2, actual.getTriangles().size());
//	}
//
//	/*
//	{
//		const auto actual = mc.Polygonise(p, { 1, 0, 1, 0, 0, 1, 0, 0 }, 0.5);
//		EXPECT_EQ(2, actual.getTriangles().size());
//	}
//	*/
//
//	{
//		const auto actual = mc.build(s, { 1, 0, 0, 0, 0, 0, 1, 0 }, 0.5);
//		EXPECT_EQ(2, actual.getTriangles().size());
//	}
//
//	/*
//	{
//		const auto actual = mc.Polygonise(p, { 0, 1, 0, 1, 0, 0, 1, 0 }, 0.5);
//		EXPECT_EQ(3, actual.getTriangles().size());
//	}
//	*/
//
//
//	{
//		const auto actual = mc.build(s, { 1, 0, 0, 1, 0, 1, 1, 0 }, 0.5);
//		EXPECT_EQ(4, actual.getTriangles().size());
//	}
//
//
//	{
//		const auto actual = mc.build(s, { 1, 1, 1, 1, 1, 1, 1, 1 }, 0.5);
//		EXPECT_EQ(0, actual.getTriangles().size());
//	}
//
//}


TEST(MarchingCubeTest, TestMarchBits)
{
	MarchingCube<float> mc;
	mc.buildTable();

	/*
	 = {
		Vector3d<float>(0, 0, 0),
		Vector3d<float>(1, 0, 0),
		Vector3d<float>(1, 1, 0),
		Vector3d<float>(0, 1, 0),
		Vector3d<float>(0, 0, 1),
		Vector3d<float>(1, 0, 1),
		Vector3d<float>(1, 1, 1),
		Vector3d<float>(0, 1, 1)
	};
	*/

	const Space3d<float> s(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));

	EXPECT_EQ(0, mc.build(s, std::bitset<8>("00000000")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00000001")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00000010")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00000011")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00000100")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00000101")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00000110")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00000111")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00001000")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00001001")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00001011")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00001101")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00001110")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00001111")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00010000")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00010001")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00010010")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00010100")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00011000")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00011001")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00011010")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00110010")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00110011")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("00111010")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("01000011")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("01101001")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("10000000")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10000001")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10000010")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10000101")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10000110")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10000100")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10001000")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10010000")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10010001")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10100000")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10100001")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10100101")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110001")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110010")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110100")).getTriangles().size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("10110101")).getTriangles().size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("10110110")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110111")).getTriangles().size());

	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11000000")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11000001")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11000010")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000011")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11000100")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000101")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000110")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11001000")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11001001")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11001010")).getTriangles().size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11001011")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11001100")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11001101")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11001110")).getTriangles().size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11001111")).getTriangles().size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11010000")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11010001")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11010010")).getTriangles().size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11010011")).getTriangles().size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11010100")).getTriangles().size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11010101")).getTriangles().size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11010110")).getTriangles().size());


//	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000111")).getTriangles().size());

	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11111100")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("11111101")).getTriangles().size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("11111110")).getTriangles().size());
	EXPECT_EQ(0, mc.build(s, std::bitset<8>("11111111")).getTriangles().size());

}

TEST(MarchingCubeTest, TestMarch)
{
	MarchingCube<float> mc;
	mc.buildTable();

	Space3d<float> s(Vector3d<float>(0, 0, 0), Vector3d<float>(10, 10, 10));
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<float> bs(s, bmp);

	EXPECT_EQ( 0, mc.march(bs).getTriangles().size() );
}