#ifndef __CRYSTAL_IO_VTK_HEADER_PART_H__
#define __CRYSTAL_IO_VTK_HEADER_PART_H__

#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

struct VTKVersion
{
	VTKVersion() :
		major( 3 ),
		minor( 0 )
	{}

	void setMajor( const int major ) { this->major = major; }

	int getMajor() const { return major; }

	void setMinor( const int minor ) { this->minor = minor; }

	int getMinor() const { return minor; }

	std::string toStr() const { return std::to_string(major) + "." + std::to_string(minor); }

	bool isValid() const {
		return major >= 0 && minor >= 0;
	}

	void read( std::istream& stream );

	void write( std::ostream& stream ) const;


private:
	int major;
	int minor;
};

struct VTKFileType {
	enum Type{
		ASCII,
		Binary,
		None,
	};

	VTKFileType() :
		type( None )
	{
	}

	VTKFileType( const Type& t ) : type( t ) {
	}

	void read( std::istream& stream );

	void write( std::ostream& stream ) const;

	bool operator==( const VTKFileType& rhs ) const {
		return this->type == rhs.type;
	}

	Type getType() const { return type; }

private:
	Type type;
};

struct VTKHeaderPart
{
	enum FileType {
	};

	VTKHeaderPart()
	{}

	VTKVersion getVersion() const { return version; }

	void setVersion( const VTKVersion& version ) { this->version = version; } 

	std::string getTitle() const { return title; }

	void setTitle( const std::string& title ) { this->title = title; }

	VTKFileType getFileType() const { return fileType; }

	void read( std::istream& stream );

	void write( std::ostream& stream ) const;

	bool isValid() {
		return title.size() <= 256;
	}


private:
	VTKVersion version;
	std::string title;
	VTKFileType fileType;
};

	}
}

#endif

#ifndef __CRYSTAL_IO_VTK_FILE_H__
#define __CRYSTAL_IO_VTK_FILE_H__

#include "VTKGeometryPart.h"
#include "VTKAttributePart.h"

#include <fstream>
#include <string>

#include <cassert>

namespace Crystal {
	namespace IO {

class VTKFile
{
public:

	VTKFile() 
	{};

	void setDiffuseData();

	void setCylinderData();

	bool read( const std::string& filename );

	bool read( std::istream& stream );

	void write( std::ostream& stream ) const {
		header.write( stream );
		geom.write( stream );
		attr.write( stream );
	};

	void setHeaderPart( const VTKHeaderPart& header ) { this->header = header; }
	
	VTKHeaderPart getHeaderPart() const { return header; }

	void setGeometryPart( const VTKGeometryPart& geom ) { this->geom = geom; }

	VTKGeometryPart getGeometryPart() const { return geom; }

	void setAttributePart( const VTKAttributePart& attr ) { this->attr = attr; }

	VTKAttributePart getAttributePart() const { return attr; }

private:
	VTKHeaderPart header;
	VTKGeometryPart geom;
	VTKAttributePart attr;
};
	}
}

#endif
