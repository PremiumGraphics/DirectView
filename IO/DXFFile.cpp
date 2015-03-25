#include "DXFFile.h"

#include <iostream>
#include <string>

using namespace Crystal::Math;
using namespace Crystal::IO;

void DXFFile::read(std::istream& stream)
{
}

void DXFFile::write(std::ostream& stream)
{
	strs = {
		"0",
		"SECTION",
		"2",
		"ENTITIES",
		"0",
		"3DFACE",
		"8",
		layerName
	};

	for (const DXFFace& f : faces) {
		const Vector3d& v0 = f.getPositions()[0];
		strs.push_back( "10");
		strs.push_back( std::to_string(v0.getX()) );
		strs.push_back( "20");
		strs.push_back( std::to_string(v0.getY()) );
		strs.push_back( "30");
		strs.push_back( std::to_string(v0.getZ()) );

		const Vector3d& v1 = f.getPositions()[1];
		strs.push_back( "11");
		strs.push_back( std::to_string(v1.getX()));
		strs.push_back( "21");
		strs.push_back( std::to_string(v1.getY()));
		strs.push_back( "31");
		strs.push_back(std::to_string(v1.getZ()));

		const Vector3d& v2 = f.getPositions()[2];
		strs.push_back( "12");
		strs.push_back( std::to_string(v2.getX()));
		strs.push_back( "22");
		strs.push_back( std::to_string(v2.getY()));
		strs.push_back( "32");
		strs.push_back( std::to_string(v2.getZ()));

		const Vector3d& v3 = f.getPositions()[3];
		strs.push_back(" 13");
		strs.push_back( std::to_string(v2.getX()));
		strs.push_back(" 23");
		strs.push_back( std::to_string(v2.getY()));
		strs.push_back( "33");
		strs.push_back( std::to_string(v2.getZ()));
	}


	std::vector<std::string> endStrs {
		"0",
		"ENDSEC",
		"0",
		"EOF"
	};

	strs.insert(strs.end(), endStrs.begin(), endStrs.end());

	for (const std::string& str : strs) {
		stream << str.c_str() << std::endl;
	}

}