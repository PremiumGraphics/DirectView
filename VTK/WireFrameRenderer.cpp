#include "stdafx.h"
#include "WireFrameRenderer.h"

#include <cassert>

#include "../Math/Vector3d.h"


#include "../Graphics/ShaderObject.h"
#include "../Graphics/Camera.h"

#include <sstream>


using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::App;

WireFrameRenderer::WireFrameRenderer()
{
}

WireFrameRenderer::~WireFrameRenderer()
{
}

namespace {
static std::stringstream getSimpleVertexSource()
{
	std::stringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in float value;" << std::endl
		<< "out vec3 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform float min;"		<< std::endl
		<< "uniform float max;"		<< std::endl
		<< "uniform float uValue;"	<< std::endl
		<< "uniform sampler1D tex;" << std::endl
		<< "uniform int isConst;"  << std::endl
		<< "void main(void)"	<< std::endl
		<< "{"	<< std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );" << std::endl
		<< "	float texCoord = 0.0;" << std::endl
		<< "    if( isConst == 0 ) {" << std::endl
		<< "		texCoord = ( value - min ) / ( max - min );"	<< std::endl
		<< "	}" << std::endl
		<< "	else {" <<	std::endl
		<< "		texCoord = ( uValue - min ) / ( max - min );"	<< std::endl
		<< "	}" << std::endl
		<< "	vColor = texture( tex, texCoord ).rgb;"	<< std::endl
		<<"}"	<< std::endl;
	return stream;
}

static std::stringstream getSimpleFragmentSource()
{
	std::stringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	fragColor.rgb = vColor;" << std::endl
		<< "	fragColor.a = 1.0;"	<< std::endl
		<< "}" << std::endl;
	return stream;
}
}

void WireFrameRenderer::build()
{
	const std::string& vStr = ::getSimpleVertexSource().str();
	const std::string& fStr = ::getSimpleFragmentSource().str();
	Shader vShader;
	Shader fShader;
	vShader.compile( vStr, Shader::Stage::VERTEX );
	fShader.compile( fStr, Shader::Stage::FRAGMENT );
	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link( vShader, fShader );
}

WireFrameRenderer::Location WireFrameRenderer::getLocations()
{
	WireFrameRenderer::Location location;

	location.projectionMatrix = glGetUniformLocation( shader.getId(), "projectionMatrix" );
	location.modelviewMatrix = glGetUniformLocation( shader.getId(), "modelviewMatrix" );
	location.min = glGetUniformLocation( shader.getId(), "min" );
	location.max = glGetUniformLocation( shader.getId(), "max" );
	location.isConst = glGetUniformLocation( shader.getId(), "isConst" );
	location.uValue = glGetUniformLocation( shader.getId(), "uValue" );

	location.position = glGetAttribLocation( shader.getId(), "position" );
	location.value = glGetAttribLocation( shader.getId(), "value" );

	return location;
}

void WireFrameRenderer::setup(const int width, const int height)
{
	assert( GL_NO_ERROR == glGetError() );

	glViewport( 0, 0, width, height );

	glUseProgram( shader.getId() );

	GLuint texture;
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_1D, texture );
	const int loc = glGetUniformLocation( shader.getId(), "tex" );
	if( loc >= 0 ) {
		glUniform1i( loc, 0 );
	}
	else {
		assert( false );
	}
}

void WireFrameRenderer::render(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices, const std::vector<ColorRGBA<float> >& texColors, const bool withSurface )
{
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );	
	glClear( GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	if( param.positions.empty() ) {
		return;
	}

	if( param.values.empty() ) {
		return;
	}

	setup( width, height );

	glActiveTexture( GL_TEXTURE0 );
	const std::vector<float>& t = toArray4( texColors );
	if( t.empty() ) {
		std::vector<float> c;
		c.push_back( 0.0 );
		c.push_back( 0.0 );
		c.push_back( 0.0 );
		c.push_back( 0.0 );
		glTexImage1D( GL_TEXTURE_1D, 0, GL_RGBA, texColors.size(), 0, GL_RGBA, GL_FLOAT, &(c.front() ) );
	}
	else {
		glTexImage1D( GL_TEXTURE_1D, 0, GL_RGBA, texColors.size(), 0, GL_RGBA, GL_FLOAT, &(t.front() ) );
	}
	glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	const Location& location = getLocations();

	glUniformMatrix4fv( location.projectionMatrix, 1, GL_FALSE, &(param.projectionMatrix.front() ) );
	glUniformMatrix4fv( location.modelviewMatrix,  1, GL_FALSE, &(param.modelviewMatrix.front() ) );
	glUniform1f( location.min, param.min );
	glUniform1f( location.max, param.max );
	glUniform1i( location.isConst, 0 );	
	
	glVertexAttribPointer( location.position, 3, GL_FLOAT, GL_FALSE, 0, &(param.positions.front()) );
	glVertexAttribPointer( location.value, 1, GL_FLOAT, GL_FALSE, 0, &(param.values.front()) );

	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	for( size_t i = 0; i < indices.size(); ++i ) {
		const std::vector<unsigned int>& is = indices[i];
		if( withSurface ) {
			glDrawElements( GL_POLYGON, is.size(), GL_UNSIGNED_INT, &(is.front() ) );
		}
		else {
			glDrawElements( GL_LINE_LOOP, is.size(), GL_UNSIGNED_INT, &(is.front() ) );
		}
	}
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );

	glBindFragDataLocation( shader.getId(), 0, "fragColor" );

	glUseProgram( 0 );

	const GLenum error = glGetError();
	if( error != GL_NO_ERROR ) {
		assert( false );
	}
}

void WireFrameRenderer::renderCells(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices, const std::vector<ColorRGBA<float> >& texColors, const bool withSurface )
{
	if( param.positions.empty() ) {
		return;
	}

	if( param.values.empty() ) {
		return;
	}

	if( ( indices.size() != param.values.size() ) ) {
		return;
	}

	setup( width, height );

	assert( GL_NO_ERROR == glGetError() );

	const std::vector<float>& t = toArray4( texColors );
	if( t.empty() ) {
		std::vector<float> c;
		c.push_back( 0.0 );
		c.push_back( 0.0 );
		c.push_back( 0.0 );
		c.push_back( 0.0 );
		glTexImage1D( GL_TEXTURE_1D, 0, GL_RGBA, texColors.size(), 0, GL_RGBA, GL_FLOAT, &(c.front() ) );
	}
	else {
		glTexImage1D( GL_TEXTURE_1D, 0, GL_RGBA, texColors.size(), 0, GL_RGBA, GL_FLOAT, &(t.front() ) );
	}
	glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	const Location& location = getLocations();

	glUniformMatrix4fv( location.projectionMatrix, 1, GL_FALSE, &(param.projectionMatrix.front() ) );
	glUniformMatrix4fv( location.modelviewMatrix,  1, GL_FALSE, &(param.modelviewMatrix.front() ) );
	glUniform1f( location.min, param.min );
	glUniform1f( location.max, param.max );
	glUniform1i( location.isConst, 1 );

	glVertexAttribPointer( location.position, 3, GL_FLOAT, GL_FALSE, 0, &(param.positions.front()) );


	glEnableVertexAttribArray( 0 );

	for( size_t i = 0; i < indices.size(); ++i ) {
		const std::vector<unsigned int>& is = indices[i];
		glUniform1f( location.uValue, param.values[i] );
		if( withSurface ) {
			glDrawElements( GL_POLYGON, is.size(), GL_UNSIGNED_INT, &(is.front() ) );
		}
		else {
			glDrawElements( GL_LINE_LOOP, is.size(), GL_UNSIGNED_INT, &(is.front() ) );
		}
	}
	glDisableVertexAttribArray( 0 );

	glBindFragDataLocation( shader.getId(), 0, "fragColor" );

	glUseProgram( 0 );

	const GLenum error = glGetError();
	if( error != GL_NO_ERROR ) {
		assert( false );
	}
}