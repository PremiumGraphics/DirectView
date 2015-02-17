#ifndef __CRYSTAL_IO_VTK_TYPE_H__
#define __CRYSTAL_IO_VTK_TYPE_H__

#include <string>
#include <cassert>

namespace Crystal {
	namespace IO {

class VTKType {
public:
	enum Type{
		BIT,
		UNSIGNED_CHAR,
		CHAR,
		UNSIGNED_SHORT,
		SHORT,
		UNSIGNED_INT,
		INT,
		UNSIGNED_LONG,
		LONG,
		FLOAT,
		DOUBLE,
		NONE,
	};

	VTKType() :
		type( NONE )
	{
	}

	VTKType( const Type& t ) :
		type( t )
	{
	}

	VTKType( const std::string& str ) {
		this->type = toType( str );
	}

	std::string toString() const {
		return toString( this->type );
	}

	void setType( const Type& t ) {
		this->type = t;
	}

	Type getType() const { 
		return type;
	}

	static Type toType( const std::string& str );

	static std::string toString( const Type& type );

	bool operator==( const VTKType& rhs ) {
		return this->type == rhs.type;
	}

private:
	Type type;
};
	}
}

#endif