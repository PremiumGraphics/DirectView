#define _CRT_SECURE_NO_DEPRECATE

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


OBJFile OBJFileReader::read(const std::string& path, const std::string& filename)
{
	const std::string fullPathName = path + "/" + filename;

	std::ifstream stream;
	stream.open(fullPathName.c_str());

	assert(stream.is_open());

	return read(stream);
}


OBJFile OBJFileReader::read(std::istream& stream )
{
	OBJFile file;
	std::string str;

	std::string header = Helper::read< std::string >(stream);

	OBJGroupSPtr group( new OBJGroup() );

	std::vector< std::string > materials;

	OBJGroupSPtrVector groups;

	Vector3dVector positions;
	Vector3dVector normals;
	Vector3dVector texCoords;

	while( !stream.eof() ) {
		if( header == "#" ) {
			std::getline( stream, str );
			//header = read< std::string >();
		}
		else if( header == "mtllib" ) {
			std::getline(stream, str);
			OBJMTLLib lib(str);
			group->setMtlLib( lib );
			//libs.push_back(lib);
		}
		else if( header == "v" ) {
			std::getline(stream, str);
			const Vector3dVector& vertices = group->readVertices(str);
			positions.insert(positions.end(), vertices.begin(), vertices.end());
		}
		else if( header == "vt" ) {
			std::getline(stream, str);
			const Vector3dVector& texs = group->readTexCoords(str);
			texCoords.insert(texCoords.end(), texs.begin(), texs.end() );
		}
		else if( header == "vn" || header == "-vn" ) {
			std::getline(stream, str);
			const Vector3dVector& norms = group->readNormals( str );
			normals.insert(normals.end(), norms.begin(), norms.end());
		}
		else if (header == "f") {
			std::getline(stream, str);
			group->readFaces(str);
		}
		else if( header == "g") {
			group->setPositions(positions);
			group->setNormals(normals);
			group->setTexCoords(texCoords);
			
			groups.push_back(group);

			std::getline( stream, str);

			group = OBJGroupSPtr(new OBJGroup());
		}
		else if( header == "usemtl" ) {
			std::getline(stream, str);
			//OBJMaterial material(str);
			const std::string name = str;
			materials.push_back(name);
		}
		header = Helper::read< std::string >(stream);
	}

	group->setPositions(positions);
	group->setNormals(normals);
	group->setTexCoords(texCoords);

	group->setMaterials(materials);

	groups.push_back(group);

	file.setGroups(groups);
	
	return file;
}


Vector3dVector OBJGroup::readVertices(const std::string& str)
{
	Vector3dVector positions;
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
	return positions;
}

Vector3dVector OBJGroup::readNormals(const std::string& str)
{
	Vector3dVector normals;
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vn");
	const float x = ::std::stof(strs[0].c_str());
	const float y = ::std::stof(strs[1].c_str());
	const float z = ::std::stof(strs[2].c_str());
	//assert( Tolerances::isEqualLoosely(Vector3d(x, y, z).getLengthSquared(), 1.0f));
	normals.push_back( Vector3d(x, y, z) );
	return normals;
}

Vector3dVector OBJGroup::readTexCoords(const std::string& str)
{
	Vector3dVector texCoords;

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
	return texCoords;
}


bool OBJFileWriter::write(const std::string& path, const std::string& filename, const OBJFile& file)
{
	const std::string fullPathName = path + "/" + filename;
	std::ofstream stream(fullPathName.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return write(stream, file);
}

bool OBJFileWriter::write(std::ostream& stream, const OBJFile& file)
{
	if (!file.getComment().empty()) {
		strs.push_back( "# " + file.getComment() );
	}

	//stream << std::endl;

	//stream << "mtllib" << " " << mtlFileName << std::endl;


	for (const OBJGroupSPtr& g : file.getGroups() ) {
		//stream << "g " << g.getName() << std::endl;
		strs.push_back("g " + g->getName());
		//strs.push_back("usemtl " + materialName);
		for (const Vector3d& pos : g->getPositions()) {
			char s[256];
			sprintf(s, "v %.4lf %.4lf %.4lf", pos.getX(), pos.getY(), pos.getZ() );
			strs.push_back(s);
		}
		for (const Vector3d& tex : g->getTexCoords() ) {
			char s[256];
			sprintf(s, "vt %.4lf %.4lf %.4lf", tex.getX(), tex.getY(), tex.getZ());
			strs.push_back(s);
		}
		for (const Vector3d& n : g->getNormals() ) {
			strs.push_back("vn " + std::to_string(n.getX()) + " " + std::to_string(n.getY()) + " " + std::to_string(n.getZ()) );
		}
		for (const OBJFace& f : g->getFaces()) {
			std::string s = f.write(stream);
			strs.push_back(s);
		}
	}


	for (const std::string& str : strs) {
		stream << str << std::endl;
	}

	return true;
}
