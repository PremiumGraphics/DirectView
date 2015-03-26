#ifndef __CRYSTAL_APP_OBJ_FILE_H__
#define __CRYSTAL_APP_OBJ_FILE_H__

#include "../Math/Vector3d.h"

#include "../IO/MTLFile.h"

#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

struct OBJFace
{
	OBJFace()
	{}

	OBJFace(const std::vector<unsigned int> vertexIndices, const std::vector<unsigned int>& texIndices = {}, const std::vector<unsigned int>& normalIndices = {}) :
		vertexIndices( vertexIndices ),
		texIndices( texIndices ),
		normalIndices( normalIndices )
	{}

	void setVertexIndices(const std::vector<unsigned int>& vertexIndices) { this->vertexIndices = vertexIndices; }

	std::vector<unsigned int> getVertexIndices() const { return vertexIndices; }

	void setTexIndices(const std::vector<unsigned int>& texIndices) { this->texIndices = texIndices; }

	std::vector<unsigned int> getTexIndices() const { return texIndices; }

	void setNormalIndices(const std::vector<unsigned int>& normalIndices) { this->normalIndices = normalIndices; }

	std::vector<unsigned int> getNormalIndices() const { return normalIndices; }

	bool hasTexIndices() const {
		return !texIndices.empty();
	}

	bool hasNormals() const {
		return !normalIndices.empty();
	}

	bool isValid() const {
		if(hasTexIndices() && !hasNormals() ) {
			return vertexIndices == texIndices;
		}
		else if (hasNormals()) {
			return vertexIndices == normalIndices;
		}
		else {
			return true;
		}
	}

	bool operator==(const OBJFace& rhs) const {
		return
			vertexIndices == rhs.vertexIndices &&
			texIndices == rhs.texIndices &&
			normalIndices == rhs.normalIndices;
	}

	std::string write(std::ostream& stream) const;

private:

	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> texIndices;
	std::vector<unsigned int> normalIndices;

};


struct OBJMTLLib {
	OBJMTLLib()
	{};

	OBJMTLLib(const std::string& name) :
		name(name)
	{}

	OBJMTLLib(const std::string& name, const std::vector< std::string >& materials) :
		name(name),
		materials(materials)
	{}

	std::string getName() const { return name; }

	std::vector< std::string > getMaterials() const { return materials; }

	bool operator==(const OBJMTLLib& rhs) const {
		return
			name == rhs.name &&
			materials == rhs.materials;
	}

private:
	std::string name;
	std::vector< std::string > materials;
};


struct OBJGroup {

	OBJGroup()
	{}

	OBJGroup( const std::string& name ) :
		name( name )
	{}

	OBJGroup( const std::string& name, const std::vector<OBJFace>& faces) :
		name( name ),
		faces( faces )
	{}

	bool operator==(const OBJGroup& rhs) const {
		return
			name == rhs.name &&
			faces == rhs.faces &&
			positions == rhs.positions &&
			normals == rhs.normals &&
			texCoords == rhs.texCoords &&
			materials == rhs.materials;
	}

	std::string getName() const { return name; }

	void setFaces(const std::vector< OBJFace>& faces) { this->faces = faces; }

	std::vector< OBJFace > getFaces() const { return faces; }

	void setPositions(const std::vector< Math::Vector3d >& positions) { this->positions = positions; }

	std::vector< Math::Vector3d > getPositions() const { return positions; }

	void setNormals(const std::vector< Math::Vector3d >& normals) { this->normals = normals; }

	void setMtlLib(const OBJMTLLib& lib) { this->mtlLib = lib; }

	std::vector< Math::Vector3d > getNormals() const { return normals; }

	void setTexCoords(const std::vector< Math::Vector3d >& texCoords) { this->texCoords = texCoords; }

	std::vector< Math::Vector3d > getTexCoords() const { return texCoords; }

	void setMaterials(const std::vector<std::string>& m) { this->materials = m; }

	void readVertices(const std::string& str);

	void readNormals(const std::string& str);

	void readTexCoords(const std::string& str);

	void readFaces(const std::string& str);


private:
	std::string name;
	std::vector< Math::Vector3d > positions;
	std::vector< Math::Vector3d > normals;
	std::vector< Math::Vector3d > texCoords;
	std::vector< OBJFace > faces;
	std::vector< std::string > materials;
	OBJMTLLib mtlLib;

};

class OBJFile {
public:
	OBJFile()
	{}

	OBJFile(std::istream& stream) {
		read(stream);
	}

	bool read( const std::string& path, const std::string& filename );

	bool read( std::istream& stream);

	bool write( const std::string& path, const std::string& filename );

	bool write(std::ostream& stream);

	void setGroups(const std::vector< OBJGroup >& groups) { this->groups = groups; }

	std::vector< OBJGroup > getGroups() const { return groups; }


	bool operator==(const OBJFile& rhs) const {
		return
			//this->mtlFileNames == rhs.mtlFileNames &&
			this->groups == rhs.groups;
	}

	std::ostream& operator<<(::std::ostream& os)
	{
		write(os);
		return os;
	}

	std::vector< std::string > getStrs() const { return strs; }

private:	
	std::string comment;
	std::vector< OBJGroup > groups;
	std::string materialName;
	std::vector< std::string > strs;
};



	}
}

#endif