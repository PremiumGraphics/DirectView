#include "gtest/gtest.h"

#include "../Math/MarchingCube.h"

using namespace Crystal::Math;

TEST(MarchingCubeTest, TestBuild)
{
	MarchingCube<float> mc;
	mc.buildTable();
	//mc.Polygonise( )
	const Position3d<float> v1(0, 0, 0 );
	const Position3d<float> v2(10, 10, 10);
	const Position3d<float> actual = mc.interpolate(0.5, v1, v2, 0.0, 1.0);
	EXPECT_EQ( Position3d<float>({ 5, 5, 5 }), actual);
}

TEST(MarchingCubeTest, TestMarch)
{
	MarchingCube<float> mc;
	mc.buildTable();

	std::array< Position3d<float>, 8 >p = {
		Position3d<float>(0, 0, 0),
		Position3d<float>(1, 0, 0),
		Position3d<float>(1, 1, 0),
		Position3d<float>(0, 1, 0),
		Position3d<float>(0, 0, 1),
		Position3d<float>(1, 0, 1),
		Position3d<float>(1, 1, 1),
		Position3d<float>(0, 1, 1)
	};
	
	const std::array< double, 8 > vs = { 0, 0, 0, 0, 1, 1, 1, 1 };
	const auto actual = mc.build( p, vs,0.5);
	EXPECT_EQ(2, actual.size());

	{
		const auto actual = mc.build(p, { 0, 0, 0, 0, 0, 0, 0, 0 }, 0.5);
		EXPECT_EQ(0, actual.size());
	}

	{
		const auto actual = mc.build(p, { 1, 0, 0, 0, 0, 0, 0, 0 },0.5);
		EXPECT_EQ(1, actual.size());
	}

	{
		const auto actual = mc.build(p, { 1, 1, 0, 0, 0, 0, 0, 0 }, 0.5);
		EXPECT_EQ(2, actual.size());
	}

	/*
	{
		const auto actual = mc.Polygonise(p, { 1, 0, 1, 0, 0, 1, 0, 0 }, 0.5);
		EXPECT_EQ(2, actual.size());
	}
	*/

	{
		const auto actual = mc.build(p, { 1, 0, 0, 0, 0, 0, 1, 0 }, 0.5);
		EXPECT_EQ(2, actual.size());
	}

	/*
	{
		const auto actual = mc.Polygonise(p, { 0, 1, 0, 1, 0, 0, 1, 0 }, 0.5);
		EXPECT_EQ(3, actual.size());
	}
	*/


	{
		const auto actual = mc.build(p, { 1, 0, 0, 1, 0, 1, 1, 0 }, 0.5);
		EXPECT_EQ(4, actual.size());
	}


	{
		const auto actual = mc.build(p, { 1, 1, 1, 1, 1, 1, 1, 1 }, 0.5);
		EXPECT_EQ(0, actual.size());
	}

}


TEST(MarchingCubeTest, TestMarchBits)
{
	MarchingCube<float> mc;
	mc.buildTable();

	std::array< Position3d<float>, 8 >p = {
		Position3d<float>(0, 0, 0),
		Position3d<float>(1, 0, 0),
		Position3d<float>(1, 1, 0),
		Position3d<float>(0, 1, 0),
		Position3d<float>(0, 0, 1),
		Position3d<float>(1, 0, 1),
		Position3d<float>(1, 1, 1),
		Position3d<float>(0, 1, 1)
	};

	EXPECT_EQ(0, mc.build(p, std::bitset<8>("00000000")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("00000001")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("00000010")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00000011")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("00000100")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00000101")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00000110")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00000111")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("00001000")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00001001")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00001011")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00001101")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00001110")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00001111")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("00010000")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00010001")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00010010")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00010100")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00011000")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00011001")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00011010")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("00110010")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("00110011")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("00111010")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("01000011")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("10110001")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("01101001")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("10000000")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("10000001")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("10000010")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("10000101")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("10000110")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("10000100")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("10001000")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("10010000")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("10010001")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("10100000")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("10100001")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("10100101")).size());
	EXPECT_EQ(2, mc.build(p, std::bitset<8>("11000000")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("11000001")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("11000010")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("11000011")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("11000100")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("11000101")).size());
	EXPECT_EQ(4, mc.build(p, std::bitset<8>("11000110")).size());
	EXPECT_EQ(3, mc.build(p, std::bitset<8>("11001000")).size());

//	EXPECT_EQ(4, mc.build(p, std::bitset<8>("11000111")).size());

	EXPECT_EQ(2, mc.build(p, std::bitset<8>("11111100")).size());
	EXPECT_EQ(1, mc.build(p, std::bitset<8>("11111110")).size());
	EXPECT_EQ(0, mc.build(p, std::bitset<8>("11111111")).size());

}