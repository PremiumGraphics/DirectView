#include "gtest/gtest.h"
 
#include "../IO/MTLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST(MTLTextureOptionTest, TestConstruct)
{
	MTLTextureOption opt;

	EXPECT_EQ( Vector3d(0.0f, 0.0f, 0.0f), opt.getOrigin() );
	EXPECT_EQ( Vector3d(1.0f, 1.0f, 1.0f), opt.getScale() );
}

TEST(MTLFileTest, TestTextureOptions)
{
	EXPECT_TRUE( MTLFile::getTextureOptions("-blendu on").getBlendU() );
	EXPECT_TRUE( MTLFile::getTextureOptions("-blendv on").getBlendV() );

	EXPECT_FALSE(MTLFile::getTextureOptions("-blendu off").getBlendU());
	EXPECT_FALSE(MTLFile::getTextureOptions("-blendv off").getBlendV());

	EXPECT_FLOAT_EQ( 0.1f, MTLFile::getTextureOptions("-boost 0.1").getBoost() );

	EXPECT_EQ( Vector3d(1.0f, 0.0f, 0.0f), MTLFile::getTextureOptions("-o 1.0 0.0 0.0").getOrigin() );
	EXPECT_EQ( Vector3d(0.1f, 0.1f, 0.1f), MTLFile::getTextureOptions("-s 0.1 0.1 0.1 ").getScale() );
	EXPECT_EQ( Vector3d(0.5f, 0.5f, 0.0f), MTLFile::getTextureOptions("-t 0.5 0.5 0.0").getTurblence() );

	EXPECT_EQ( 255, MTLFile::getTextureOptions("-texres 255").getResolution() );

	EXPECT_TRUE( MTLFile::getTextureOptions("-clamp on").getClamp() );
	EXPECT_FALSE( MTLFile::getTextureOptions("-clamp off").getClamp() );

	EXPECT_EQ( 'r', MTLFile::getTextureOptions("-imfchan r").getImfChan() );
	EXPECT_EQ( 'g', MTLFile::getTextureOptions("-imfchan g").getImfChan() );
	EXPECT_EQ( 'b', MTLFile::getTextureOptions("-imfchan b").getImfChan() );
	EXPECT_EQ( 'm', MTLFile::getTextureOptions("-imfchan m").getImfChan() );
	EXPECT_EQ( 'l', MTLFile::getTextureOptions("-imfchan l").getImfChan() );
	EXPECT_EQ( 'z', MTLFile::getTextureOptions("-imfchan z").getImfChan() );
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