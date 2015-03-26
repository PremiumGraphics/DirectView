#include "OBJFile.h"

#include <fstream>
#include <cassert>
#include <vector>

#include "../Math/Vector3d.h"

#include "Helper.h"

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

std::string OBJFace::write(std::ostream& stream) const
{
	std::string s;
	s += "f";
	if ( hasTexIndices() && !hasNormals()) {
		for (size_t i = 0; i < vertexIndices.size(); ++i) {
			s += " " + std::to_string(vertexIndices[i]) + "/" + std::to_string(texIndices[i]);
		}
	}
	else if (hasTexIndices() && hasNormals()) {
		for (size_t i = 0; i < vertexIndices.size(); ++i) {
			s += " " + std::to_string(vertexIndices[i]) + "/" + std::to_string(texIndices[i]) + "/" + std::to_string(normalIndices[i]);
		}
	}
	else if (hasNormals()) {
		for (size_t i = 0; i < vertexIndices.size(); ++i) {
			s += " " + std::to_string(vertexIndices[i]) + "//" + std::to_string(normalIndices[i]);
		}
	}
	else {
		for (const unsigned int i : vertexIndices) {
			s += " " + std::to_string(i);
		}
	}
	return s;
}


bool OBJFile::read(const std::string& path, const std::string& filename)
{
	const std::string fullPathName = path + "/" + filename;

	std::ifstream stream;
	stream.open(fullPathName.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

void OBJGroup::readFaces(const std::string& str)
{
	std::vector< std::string >& strs = Helper::split(str, ' ');

	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> texIndices;
	std::vector<unsigned int> normalIndices;
	//assert(strs.front() == "f");
	OBJFace face;
	for (unsigned int i = 0; i < strs.size(); ++i) {
		if (strs[i].empty()) {
			continue;
		}
		std::string::size_type pos( strs[i].find("//"));
		if (pos != std::string::npos) {
			strs[i].replace( pos, 2, "/ /");
		}

		std::vector<std::string>& splitted = Helper::split(strs[i], '/');
		const int index = std::stoi(splitted[0]);
		vertexIndices.push_back(index);
		if (splitted.size() >= 2 && splitted[1] != " " ) {
			const int index = std::stoi(splitted[1]);
			texIndices.push_back(index);
		}
		if (splitted.size() >= 3) {
			const int index = std::stoi(splitted[2]);
			normalIndices.push_back(index);
		}
	}
	faces.push_back( OBJFace( vertexIndices, texIndices, normalIndices ) );
}

bool OBJFile::read(std::istream& stream )
{
	std::string str;

	std::string header = Helper::read< std::string >(stream);

	OBJGroup group;

	std::vector< std::string > materials;

	while( !stream.eof() ) {
		if( header == "#" ) {
			std::getline( stream, str );
			//header = read< std::string >();
		}
		else if( header == "mtllib" ) {
			std::getline(stream, str);
			OBJMTLLib lib(str);
			group.setMtlLib( lib );
			//libs.push_back(lib);
		}
		else if( header == "v" ) {
			std::getline(stream, str);
			group.readVertices(str);
		}
		else if( header == "vt" ) {
			std::getline(stream, str);
			group.readTexCoords(str);
		}
		else if( header == "vn" || header == "-vn" ) {
			std::getline(stream, str);
			group.readNormals( str );
		}
		else if (header == "f") {
			std::getline(stream, str);
			group.readFaces(str);
		}
		else if( header == "g") {
			groups.push_back(group);

			std::getline( stream, str);

			group = OBJGroup( str );
		}
		else if( header == "usemtl" ) {
			std::getline(stream, str);
			//OBJMaterial material(str);
			const std::string name = str;
			materials.push_back(name);
		}
		header = Helper::read< std::string >(stream);
	}
	group.setMaterials(materials);

	groups.push_back(group);
	
	return true;
}


void OBJGroup::readVertices(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "v");

	const float x = std::stof(strs[0].c_str());
	const float y = std::stof(strs[1].c_str());
	const float z = std::stof(strs[2].c_str());
	if (strs.size() == 4) {
		const float w = ::std::stof(strs[3].c_str());
		positions.push_back( Vector3d(x, y, z) );
	}
	else {
		positions.push_back( Vector3d(x, y, z) );
	}
}

void OBJGroup::readNormals(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vn");
	const float x = ::std::stof(strs[0].c_str());
	const float y = ::std::stof(strs[1].c_str());
	const float z = ::std::stof(strs[2].c_str());
	//assert( Tolerances::isEqualLoosely(Vector3d(x, y, z).getLengthSquared(), 1.0f));
	normals.push_back( Vector3d(x, y, z) );
}

void OBJGroup::readTexCoords(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vt");
	const float u = ::std::stof(strs[0]);
	const float v = ::std::stof(strs[1]);
	if (strs.size() == 3) {
		const float w = std::stof(strs[2]);
		texCoords.push_back( Vector3d(u, v, w) );
	}
	else {
		texCoords.push_back( Vector3d(u, v, 0.0f) );
	}
}


bool OBJFile::write(const std::string& path, const std::string& filename)
{
	const std::string fullPathName = path + "/" + filename;
	std::ofstream stream(fullPathName.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return write(stream);
}

bool OBJFile::write(std::ostream& stream)
{
	//strs.push_back( "# " + comment );

	//stream << std::endl;

	//stream << "mtllib" << " " << mtlFileName << std::endl;


	for (const OBJGroup& g : groups) {
		//stream << "g " << g.getName() << std::endl;
		strs.push_back("g " + g.getName());
		//strs.push_back("usemtl " + materialName);
		for (const Vector3d& pos : g.getPositions()) {
			char s[256];
			sprintf(s, "v %.4lf %.4lf %.4lf", pos.getX(), pos.getY(), pos.getZ() );
			strs.push_back(s);
		}
		for (const Vector3d& tex : g.getTexCoords() ) {
			strs.push_back("vt " + std::to_string(tex.getX()) + " " + std::to_string(tex.getY()) + " " + std::to_string(tex.getZ()));
		}
		for (const Vector3d& n : g.getNormals() ) {
			strs.push_back("vn " + std::to_string(n.getX()) + " " + std::to_string(n.getY()) + " " + std::to_string(n.getZ()) );
		}
		for (const OBJFace& f : g.getFaces()) {
			std::string s = f.write(stream);
			/*
			s += "f";
			if (f.hasTexIndices() && !f.hasNormals()) {
				for (size_t i = 0; i < f.getVertexIndices().size(); ++i) {
					s += " " + std::to_string( f.getVertexIndices()[i] ) + "/" + std::to_string( f.getTexIndices()[i] );
				}
			}
			else if (f.hasTexIndices() && f.hasNormals()) {
				for (size_t i = 0; i < f.getVertexIndices().size(); ++i) {
					s += " " + std::to_string( f.getVertexIndices()[i] ) + "/" + std::to_string( f.getTexIndices()[i] ) + "/" + std::to_string( f.getNormalIndices()[i] );
				}
			}
			else if (f.hasNormals()) {
				for (size_t i = 0; i < f.getVertexIndices().size(); ++i) {
					s += " " + std::to_string(f.getVertexIndices()[i]) + "//" + std::to_string(f.getNormalIndices()[i]);
				}
			}
			else {
				for (const unsigned int i : f.getVertexIndices()) {
					s += " " + std::to_string(i);
				}
			}
			*/
			strs.push_back(s);
		}
	}


	for (const std::string& str : strs) {
		stream << str << std::endl;
	}

	return true;
}
