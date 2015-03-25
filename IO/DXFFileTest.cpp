#include "gtest/gtest.h"

#include "../IO/DXFFile.h"

using namespace Crystal::IO;

TEST(DXFFileTest, TestWrite)
{
	std::ostringstream stream;
	DXFFile file;
	file.write(stream);
}