#include "gtest/gtest.h"

#include "BitMarchingCube.h"

using namespace Crystal::Math;

TEST(BitMarchingCubeTest, Test)
{
	BitMarchingCube<float> mc;

	const Space3d<float> s(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));

	EXPECT_EQ(0, mc.build(s, std::bitset<8>("00000000")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00000001")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00000010")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00000011")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00000100")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00000101")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00000110")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00000111")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00001000")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00001001")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00001011")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00001101")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00001110")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00001111")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("00010000")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00010001")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00010010")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00010100")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00011000")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00011001")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00011010")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("00110010")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("00110011")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("00111010")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("01000011")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("01101001")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("10000000")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10000001")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10000010")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10000101")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10000110")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10000100")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10001000")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10010000")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10010001")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("10100000")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("10100001")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10100101")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110001")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110010")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110100")).size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("10110101")).size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("10110110")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("10110111")).size());

	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11000000")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11000001")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11000010")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000011")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11000100")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000101")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000110")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11001000")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11001001")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11001010")).size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11001011")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11001100")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11001101")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11001110")).size());
	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11001111")).size());
	EXPECT_EQ(3, mc.build(s, std::bitset<8>("11010000")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11010001")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11010010")).size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11010011")).size());
	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11010100")).size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11010101")).size());
	EXPECT_EQ(5, mc.build(s, std::bitset<8>("11010110")).size());


	//	EXPECT_EQ(4, mc.build(s, std::bitset<8>("11000111")).size());

	EXPECT_EQ(2, mc.build(s, std::bitset<8>("11111100")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("11111101")).size());
	EXPECT_EQ(1, mc.build(s, std::bitset<8>("11111110")).size());
	EXPECT_EQ(0, mc.build(s, std::bitset<8>("11111111")).size());


}

TEST(MarchingCubeTest, TestMarchBitSpace)
{
	using GeomType = float;


	BitMarchingCube<GeomType> mc;

	Space3d<GeomType> s(Vector3d<GeomType>(0, 0, 0), Vector3d<GeomType>(10, 10, 10));
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<GeomType> bs(s, bmp);

	EXPECT_EQ(0, mc.march(bs).size());
}
