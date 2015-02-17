#include "gtest/gtest.h"
 
#include "../IO/MTLFile.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;

using namespace Crystal::Math;


#include "Helper.h"

bool readOnOff(const std::string& str)
{
	if (str == "on") {
		return true;
	}
	else if( str == "off" ) {
		return false;
	}
	else {
		assert(false);
		return false;
	}
}

MTLTextureOption getTextureOptions(const std::string& str)
{
	std::stringstream stream(str);
	MTLTextureOption options;
	std::string nextStr = Helper::readNextString(stream);
	while (!nextStr.empty() && nextStr.front() == '-') {
		std::string str = Helper::read<std::string>(stream);
		if (str == "-blendu") {
			str = Helper::read<std::string>(stream);
			options.blendu = readOnOff(str);
		}
		else if (str == "-blendv") {
			str = Helper::read<std::string>(stream);
			options.blendv = readOnOff(str);
		}
		else if (str == "-boost") {
			options.boost = Helper::read<float>(stream);
		}
		else if (str == "-mm") {
			options.baseValue = Helper::read<float>(stream);
			options.gainValue = Helper::read<float>(stream);
		}
		else if (str == "-o") {
			options.origin = Helper::readVector(stream);
		}
		else if (str == "-s") {
			options.scale = Helper::readVector(stream);
		}
		else if (str == "-t") {
			options.turblence = Helper::readVector(stream);
		}
		else if (str == "-texres") {
			options.resolution = Helper::read<int>(stream);
		}
		else if (str == "-clamp") {
			str = Helper::read<std::string>(stream);
			options.clamp = readOnOff(str);
		}
		else if (str == "-bm") {
			options.bm = Helper::read<float>(stream);
		}
		else if (str == "-imfchan") {
			const char c = Helper::read<char>(stream);
			//r | g | b | m | l | z
			assert(c == 'r' || c == 'g' || c == 'b' || c == 'm' || c == 'l' || c == 'z');
			options.imfchan = c;
		}
		nextStr = Helper::readNextString(stream);
	}
	return options;
}

TEST(MTLFileTest, TestTextureOptions)
{
	EXPECT_TRUE( getTextureOptions("-blendu on").blendu );
	EXPECT_TRUE( getTextureOptions("-blendv on").blendv );

	EXPECT_FALSE( getTextureOptions("-blendu off").blendu);
	EXPECT_FALSE( getTextureOptions("-blendv off").blendv);

	EXPECT_FLOAT_EQ( 0.1f, getTextureOptions("-boost 0.1").boost );

	EXPECT_EQ( Vector3d(1.0f, 0.0f, 0.0f), getTextureOptions("-o 1.0 0.0 0.0").origin );
	EXPECT_EQ( Vector3d(0.1f, 0.1f, 0.1f), getTextureOptions("-s 0.1 0.1 0.1 ").scale );
	EXPECT_EQ( Vector3d(0.5f, 0.5f, 0.0f), getTextureOptions("-t 0.5 0.5 0.0").turblence );

	EXPECT_EQ( 255, getTextureOptions("-texres 255").resolution);

	EXPECT_TRUE( getTextureOptions("-clamp on").clamp );
	EXPECT_FALSE( getTextureOptions("-clamp off").clamp );

	EXPECT_EQ( 'r', getTextureOptions("-imfchan r").imfchan );
	EXPECT_EQ( 'g', getTextureOptions("-imfchan g").imfchan );
	EXPECT_EQ( 'b', getTextureOptions("-imfchan b").imfchan );
	EXPECT_EQ( 'm', getTextureOptions("-imfchan m").imfchan );
	EXPECT_EQ( 'l', getTextureOptions("-imfchan l").imfchan );
	EXPECT_EQ( 'z', getTextureOptions("-imfchan z").imfchan );
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