#include "gtest/gtest.h"

#include "CGBFile.h"
#include <vector>
#include <string>


using namespace tinyxml2;
using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(CGBFileTest, TestBuild)
{
	CGBFile file;
	Space3d<float> space;
	Grid3d<float> grid(10,20,30);
	Volume3d<float> v(space, grid);
	std::shared_ptr< XMLDocument > doc = file.buildXML(v);
	doc->Print();
}

TEST(CGBFileTest, TestToImageFileName)
{
	CGBFile file;
	const auto& actual = file.toImageFileName("./", "Test", 0);
	EXPECT_EQ("./Test0", actual);
}

TEST(CGBFileTest, TestGetImageFileNames)
{
	CGBFile file;
	Space3d<float> space;
	Grid3d<float> grid(1, 2, 3);
	Volume3d<float> v(space, grid);
	const auto& result = file.getImageFileNames("./", "Test", v);
	EXPECT_EQ( 3, result.size() );
	//EXPECT_EQ(3, result.size());
}
/*
TEST(CGBFileTest, TestParse)
{

}
*/