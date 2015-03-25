#include "gtest/gtest.h"

#include "../IO/DXFFile.h"

using namespace Crystal::IO;

TEST(DXFFileTest, TestWrite)
{
	std::ostringstream stream;
	DXFFile file;
	file.write(stream);

	const std::vector< std::string >& strs = file.getStrs();

	/*
	std::stringstream estream;
	estream << "0" << std::endl;
	estream << "SECTION" << std::endl;
	estream << "2" << std::endl;
	estream << "ENTITIES" << std::endl;
	estream << "0" << std::endl;
	estream << "ENDSEC" << std::endl;
	estream << "0" << std::endl;
	estream << "EOF" << std::endl;
	*/



	EXPECT_EQ( "0", strs[0]);
	EXPECT_EQ( "SECTION", strs[1]);
	EXPECT_EQ( "2", strs[2]);

}