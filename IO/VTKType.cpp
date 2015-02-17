#include "VTKType.h"

using namespace Crystal::IO;

VTKType::Type VTKType::toType( const std::string& str ) {
	if( str == "bit" ) {
		return Type::BIT;
	}
	else if( str == "unsigned_char" ) {
		return Type::UNSIGNED_CHAR;
	}
	else if( str == "char" ) {
		return Type::CHAR;
	}
	else if( str == "unsigned_short" ) {
		return Type::UNSIGNED_SHORT;
	}
	else if( str == "short" ) {
		return Type::SHORT;
	}
	else if( str == "unsigned_int" ) {
		return Type::UNSIGNED_INT;
	}
	else if( str == "int" ) {
		return Type::INT;
	}
	else if( str == "unsigned_long" ) {
		return Type::UNSIGNED_LONG;
	}
	else if( str == "long" ) {
		return Type::LONG;
	}
	else if( str == "float" ) {
		return Type::FLOAT;
	}
	else if( str == "double" ) {
		return Type::DOUBLE;
	}
	else {
		assert( false );
		return Type::NONE;
	}
}

std::string VTKType::toString( const Type& type )
{
	switch( type ) {
	case BIT :
		return "bit";
	case UNSIGNED_CHAR :
		return "unsigned_char";
	case CHAR :
		return "char";
	case UNSIGNED_SHORT :
		return "unsigned_short";
	case SHORT :
		return "short";
	case UNSIGNED_INT :
		return "unsigned_int";
	case INT :
		return "int";
	case UNSIGNED_LONG :
		return "unsigned_long";
	case LONG :
		return "long";
	case FLOAT :
		return "float";
	case DOUBLE :
		return "double";
	default:
		assert( false );
		return std::string();
	}
}
