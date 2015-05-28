#ifndef __CRYSTAL_APP_OBJ_FILE_H__
#define __CRYSTAL_APP_OBJ_FILE_H__

#include "../Math/Vector.h"

#include "../IO/MTLFile.h"

#include <fstream>
#include <string>
#include <vector>

namespace Crystal {
	namespace IO {

typedef std::vector<int> OBJIndices;

struct OBJFace
{
	OBJFace()
	{}

	OBJFace(const OBJIndices& vertexIndices, const OBJIndices& texIndices = {}, const OBJIndices& normalIndices = {}) :
		vertexIndices( vertexIndices ),
		texIndices( texIndices ),
		normalIndices( normalIndices )
	{}

	void setVertexIndices(const OBJIndices& vertexIndices) { this->vertexIndices = vertexIndices; }

	OBJIndices getVertexIndices() const { return vertexIndices; }

	void setTexIndices(const OBJIndices& texIndices) { this->texIndices = texIndices; }

	OBJIndices getTexIndices() const { return texIndices; }

	void setNormalIndices(const OBJIndices& normalIndices) { this->normalIndices = normalIndices; }

	OBJIndices getNormalIndices() const { return normalIndices; }

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

	std::string usemtlname;

private:
	OBJIndices vertexIndices;
	OBJIndices texIndices;
	OBJIndices normalIndices;
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
			materials == rhs.materials;
	}

	std::string getName() const { return name; }

	void setFaces(const std::vector< OBJFace>& faces) { this->faces = faces; }

	std::vector< OBJFace > getFaces() const { return faces; }

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positions = positions; }

	std::vector< Math::Vector3d<float> > getPositions() const { return positions; }

	void setNormals(const std::vector< Math::Vector3d<float> >& normals) { this->normals = normals; }

	std::vector< Math::Vector3d<float> > getNormals() const { return normals; }

	void setMtlLib(const OBJMTLLib& lib) { this->mtlLib = lib; }

	void setTexCoords(const std::vector< Math::Vector3d<float> >& texCoords) { this->texCoords = texCoords; }

	std::vector< Math::Vector3d<float> > getTexCoords() const { return texCoords; }

	void setMaterials(const std::vector<std::string>& m) { this->materials = m; }

	Math::Vector3d<float> readVertices(const std::string& str);

	Math::Vector3d<float> readVector3d(const std::string& str);

	OBJFace readFaces(const std::string& str);


private:
	std::string name;
	std::vector< OBJFace > faces;
	std::vector< std::string > materials;
	OBJMTLLib mtlLib;
	Math::Vector3dVector<float> positions;
	Math::Vector3dVector<float> normals;
	Math::Vector3dVector<float> texCoords;

};

typedef std::shared_ptr< OBJGroup > OBJGroupSPtr;
typedef std::vector< OBJGroupSPtr > OBJGroupSPtrVector;

struct OBJFile {
	bool isValid() const {
		return true;	//�@TODO.
	}

	void setComment(const std::string& comment) { this->comment = comment; }

	std::string getComment() const { return comment; }

	void setGroups(const OBJGroupSPtrVector& groups) { this->groups = groups; }

	OBJGroupSPtrVector getGroups() const { return groups; }

	std::string getMaterialName() const { return materialName; }

private:
	std::string comment;
	OBJGroupSPtrVector groups;
	std::string materialName;

};

class OBJFileWriter {
public:
	bool write(const std::string& path, const std::string& filename, const OBJFile& file);

	bool write(std::ostream& stream, const OBJFile& file);

	/*
	std::ostream& operator<<(::std::ostream& os)
	{
		write(os);
		return os;
	}
	*/

	std::vector< std::string > getStrs() const { return strs; }

private:
	std::vector< std::string > strs;
};

class OBJFileReader {
public:
	OBJFileReader()
	{}

	OBJFileReader(std::istream& stream) {
		read(stream);
	}

	OBJFile read(const std::string& path, const std::string& filename);

	OBJFile read(std::istream& stream);
};



static ::std::ostream& operator<<(::std::ostream& os, const OBJMTLLib& lib)
{
	os << "name " << lib.getName() << std::endl;
	for (const std::string& m : lib.getMaterials()) {
		os << m << std::endl;
	}
	return os;
}

	}
}

#endif