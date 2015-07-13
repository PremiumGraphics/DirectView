#include "gtest/gtest.h"

#include "CGBFile.h"

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

/*
TEST(CGBFileTest, TestParse)
{

}
*/