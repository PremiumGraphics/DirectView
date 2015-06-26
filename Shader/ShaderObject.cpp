#include "GLee.h"

#include "ShaderObject.h"
//#include "TextureObject.h"
#include "../Math/Matrix.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

ShaderUnit::ShaderUnit(void) :
	id( -1 )
{
}

ShaderUnit::~ShaderUnit(void)
{
	clear();
}

void ShaderUnit::clear()
{
	if( id != -1 ) {
		glDeleteShader( id );
	}
}

bool ShaderUnit::compile( const std::string& source, const ShaderUnit::Stage stage )
{
	clear();
	if( stage == ShaderUnit::Stage::VERTEX ) {
		id = glCreateShader( GL_VERTEX_SHADER );
	}
	else if( stage == ShaderUnit::Stage::FRAGMENT ) {
		id = glCreateShader( GL_FRAGMENT_SHADER );
	}
	else if( stage == ShaderUnit::Stage::GEOMETRY ) {
		id = glCreateShader( GL_GEOMETRY_SHADER_ARB );
	}
	else {
		assert( false );
		return false;
	}
	const GLchar *strPtr[1];
	strPtr[0] = source.c_str();
	glShaderSource( id, 1, strPtr, NULL );

	glCompileShader( id );

	GLint success;
	glGetShaderiv( id, GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog( id, 2048, NULL, infoLog );
	log += infoLog;
	//assert( success != 0 );
	//return ( success != 0 );

	if( success == 0 ) {
		return false;
	}

	if( glGetError() != GL_NO_ERROR ) {
		return false;
	}
	return true;
}



ShaderObject::ShaderObject(void) :
	id( -1 )
{
}

ShaderObject::~ShaderObject(void)
{
	clear();
}

void ShaderObject::clear()
{
	glUseProgram( 0 );
	if( id != -1 ) {
		glDeleteProgram( id );
	}
}

void ShaderObject::link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader )
{
	clear();

	assert( glGetError() == GL_NO_ERROR );
	
	id = glCreateProgram();
	glAttachShader( id, vertexShader.getID() );
	glAttachShader( id, fragmentShader.getID() );
	
	GLint success;
	glLinkProgram( id );
	glGetProgramiv( id, GL_LINK_STATUS, &success );

	GLchar infoLog[2048];
	glGetProgramInfoLog( id, 2048, NULL, infoLog );
	log += infoLog;

	assert( success );

	assert( glGetError() == GL_NO_ERROR );
}

void ShaderObject::link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader, const ShaderUnit& geometryShader )
{
	clear();

	assert( glGetError() == GL_NO_ERROR );
	
	id = glCreateProgram();
	glAttachShader( id, vertexShader.getID() );
	glAttachShader( id, fragmentShader.getID() );
	glAttachShader( id, geometryShader.getID() );
	
	GLint success;
	glLinkProgram( id );
	glGetProgramiv( id, GL_LINK_STATUS, &success );

	GLchar infoLog[2048];
	glGetProgramInfoLog( id, 2048, NULL, infoLog );
	log += infoLog;

	assert( success );

	assert( glGetError() == GL_NO_ERROR );
}


bool ShaderUtil::isValidUniform(const std::string& name, GLuint location)
{
	if( location != -1 ) {
		return true;
	}
	std::cout << "uniform <" << name << "> not found." << std::endl;
	return false;
}

void ShaderUtil::setUniform(const int id, const std::string& name, const int value)
{
	GLuint textureLoc = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, textureLoc ) );
	glUniform1i( textureLoc, value );
}

void ShaderUtil::setUniform( const int id, const std::string& name, const float value )
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniform1f( location, value );
}

void ShaderUtil::setUniformVector( const int id, const std::string& name, GLfloat* value)
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniform3fv( location, 1, value); 
}

void ShaderUtil::setUniformVector( const int id, const std::string& name, const std::vector< GLfloat >& value )
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniform3fv( location, 1, &( value.front() ) ); 
}

void ShaderUtil::setUniformMatrix( const int id, const std::string& name, const Matrix4d<float>& matrix )
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	setUniformMatrix( location, matrix );
}

void ShaderUtil::setUniformMatrix( unsigned int location, const Matrix4d< float >& matrix )
{
	std::vector< float > values = matrix.toArray4x4();
	glUniformMatrix4fv( location, 1, GL_FALSE, &( values.front() ) );
}
