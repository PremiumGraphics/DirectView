#include "gtest/gtest.h"

#include "VTKType.h"

using namespace Crystal::IO;

TEST( VTKTypeTest, TestToType )
{
	EXPECT_EQ( VTKType::BIT,			VTKType::toType( "bit" ) );
	EXPECT_EQ( VTKType::UNSIGNED_CHAR,	VTKType::toType( "unsigned_char" ) );
	EXPECT_EQ( VTKType::CHAR,			VTKType::toType( "char" ) );
	EXPECT_EQ( VTKType::UNSIGNED_SHORT, VTKType::toType( "unsigned_short" )  );
	EXPECT_EQ( VTKType::SHORT,			VTKType::toType( "short" ) );
	EXPECT_EQ( VTKType::UNSIGNED_INT,	VTKType::toType( "unsigned_int" ) );
	EXPECT_EQ( VTKType::INT,			VTKType::toType( "int" ) );
	EXPECT_EQ( VTKType::UNSIGNED_LONG,	VTKType::toType( "unsigned_long" ) );
	EXPECT_EQ( VTKType::LONG,			VTKType::toType( "long" ) );
	EXPECT_EQ( VTKType::FLOAT,			VTKType::toType( "float" ) );
	EXPECT_EQ( VTKType::DOUBLE,			VTKType::toType( "double" ) );
}

TEST( VTKTypeTest, TestToString )
{
	EXPECT_EQ( "bit",				VTKType::toString( VTKType::BIT ) );
	EXPECT_EQ( "unsigned_char",		VTKType::toString( VTKType::UNSIGNED_CHAR ) );
	EXPECT_EQ( "char",				VTKType::toString( VTKType::CHAR ) );
	EXPECT_EQ( "unsigned_short",	VTKType::toString( VTKType::UNSIGNED_SHORT ) );
	EXPECT_EQ( "short",				VTKType::toString( VTKType::SHORT ) );
	EXPECT_EQ( "unsigned_int",		VTKType::toString( VTKType::UNSIGNED_INT ) );
	EXPECT_EQ( "int",				VTKType::toString( VTKType::INT ) );
	EXPECT_EQ( "unsigned_long",		VTKType::toString( VTKType::UNSIGNED_LONG ) );
	EXPECT_EQ( "long",				VTKType::toString( VTKType::LONG ) );
	EXPECT_EQ( "float",				VTKType::toString( VTKType::FLOAT ) );
	EXPECT_EQ( "double",			VTKType::toString( VTKType::DOUBLE ) );
}