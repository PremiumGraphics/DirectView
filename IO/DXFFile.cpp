#include "DXFFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

void DXFFile::read(std::istream& stream)
{
}

void DXFFile::write(std::ostream& stream)
{
	stream << "0" << std::endl;
	stream << "SECTION" << std::endl;
	stream << "2" << std::endl;
	stream << "ENTITIES" << std::endl;
	stream << "0" << std::endl;
	stream << "3DFACE" << std::endl;
	stream << "8" << std::endl;
	stream << layerName.c_str() << std::endl;

	/*
	for (const Vector3d& v : positions) {
		stream << "10" << std::endl;
		stream << v.getX() << std::endl;
		stream << "20" << std::endl;
		stream << v.getY() << std::endl;
		stream << "30" << std::endl;
		stream << v.getZ() << std::endl;
		stream << "11" << std::endl;
		stream << v.getX()
	}
	*/
}