#include "gtest/gtest.h"
 
#include "../IO/MTLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;


TEST(MTLFileTest, TestTextureOptions)
{
	EXPECT_TRUE( MTLFile::getTextureOptions("-blendu on").blendu );
	EXPECT_TRUE( MTLFile::getTextureOptions("-blendv on").blendv );

	EXPECT_FALSE( MTLFile::getTextureOptions("-blendu off").blendu);
	EXPECT_FALSE( MTLFile::getTextureOptions("-blendv off").blendv);

	EXPECT_FLOAT_EQ( 0.1f, MTLFile::getTextureOptions("-boost 0.1").boost );

	EXPECT_EQ( Vector3d(1.0f, 0.0f, 0.0f), MTLFile::getTextureOptions("-o 1.0 0.0 0.0").origin );
	EXPECT_EQ( Vector3d(0.1f, 0.1f, 0.1f), MTLFile::getTextureOptions("-s 0.1 0.1 0.1 ").scale );
	EXPECT_EQ( Vector3d(0.5f, 0.5f, 0.0f), MTLFile::getTextureOptions("-t 0.5 0.5 0.0").turblence );

	EXPECT_EQ( 255, MTLFile::getTextureOptions("-texres 255").resolution);

	EXPECT_TRUE( MTLFile::getTextureOptions("-clamp on").clamp );
	EXPECT_FALSE( MTLFile::getTextureOptions("-clamp off").clamp );

	EXPECT_EQ( 'r', MTLFile::getTextureOptions("-imfchan r").imfchan);
	EXPECT_EQ( 'g', MTLFile::getTextureOptions("-imfchan g").imfchan);
	EXPECT_EQ( 'b', MTLFile::getTextureOptions("-imfchan b").imfchan);
	EXPECT_EQ( 'm', MTLFile::getTextureOptions("-imfchan m").imfchan);
	EXPECT_EQ( 'l', MTLFile::getTextureOptions("-imfchan l").imfchan);
	EXPECT_EQ( 'z', MTLFile::getTextureOptions("-imfchan z").imfchan);
}


::std::ostream& operator<<(::std::ostream& os, const ColorRGB<float>& c) {
	return os << c.getRed() << c.getGreen() << c.getBlue() << std::endl;
}


::std::ostream& operator<<(::std::ostream& os, const MTL& mtl) {
	return os << mtl.ambient << mtl.diffuse << mtl.specular << std::endl;
}

TEST(MTLFileTest, TestRead)
{
	std::stringstream stream;
	stream
		<< "newmtl FrontColor" << std::endl
		<< "Ka 0.0 0.0 0.0" << std::endl
		<< "Kd 1.0 1.0 1.0" << std::endl
		<< "Ks 0.1 0.1 0.1" << std::endl
		<< "illum 0" << std::endl;

	MTLFile file;
	file.read(stream);
	const std::vector<MTL>& actual = file.getMaterials();
	
	MTL expected;
	expected.name = "FrontColor";
	expected.ambient = ColorRGB<float>(0.0f, 0.0f, 0.0f);
	expected.diffuse = ColorRGB<float>(1.0f, 1.0f, 1.0f);
	expected.specular = ColorRGB<float>(0.1f, 0.1f, 0.1f);

	const std::vector<MTL> expecteds = { expected };
	EXPECT_EQ( expecteds, actual);
}

TEST(MTLFileTest, TestReadTexture)
{
	std::stringstream stream;
	stream
		<< "newmtl name" << std::endl
		<< "map_Ka ambient.png" << std::endl
		<< "map_Kd diffuse.png" << std::endl
		<< "map_Ks shininess.png" << std::endl
		<< "bump bump.png" << std::endl;

	MTLFile file;
	file.read(stream);
	const std::vector<MTL>& actual = file.getMaterials();

	MTL expected;
	expected.name = "name";
	expected.ambientTexture = "ambient.png";
	expected.diffuseTexture = "diffuse.png";
	expected.shininessTexture = "shininess.png";
	expected.bumpTexture = "bump.png";

	const std::vector<MTL> expecteds = { expected };
	EXPECT_EQ(expecteds, actual);
}