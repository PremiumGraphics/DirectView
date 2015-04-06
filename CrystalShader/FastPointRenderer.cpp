#include "FastPointRenderer.h"

#include <cassert>

#include "../Math/Vector3d.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

FastPointRenderer::FastPointRenderer()
{
}

FastPointRenderer::~FastPointRenderer()
{
}

namespace {
	GLuint positionLocation = 0;
	GLuint valueLocation = 1;
	GLuint texture;
}
static std::stringstream getVertexSource()
{
	std::stringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in float value;" << std::endl
		<< "out vec3 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform float min;"	<< std::endl
		<< "uniform float max;"	<< std::endl
		<< "uniform sampler1D tex;" << std::endl
		<< "void main(void)"	<< std::endl
		<< "{"	<< std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );" << std::endl
		<< "	float texCoord = (value - min) / ( max - min );"	<< std::endl
		<< "	vColor = texture( tex, texCoord ).rgb;"	<< std::endl
		<<"}"	<< std::endl;
	return stream;
}


static std::stringstream getFragmentSource()
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

void FastPointRenderer::build()
{
	Graphics::Shader vShader;
	Graphics::Shader fShader;
	vShader.compile(getVertexSource().str(), Graphics::Shader::Stage::VERTEX);
	fShader.compile(getFragmentSource().str(), Graphics::Shader::Stage::FRAGMENT);
	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link( vShader, fShader );

	glBindAttribLocation( shader.getId(), positionLocation, "position" );
	glBindAttribLocation( shader.getId(), valueLocation, "value" );

}

void FastPointRenderer::render( const int width, const int height, const Camera<float>* camera, const std::vector<float>& positions, const std::vector<float>& values, const float min, const float max, const std::vector<ColorRGBA<float> >& texColors, const float pointSize )
{
	if( positions.empty() ) {
		return;
	}

	const Matrix4d<float>& perspectiveMatrix = camera->getPerspectiveMatrix();

	std::vector< float > bColor;
	bColor.push_back( 0.0f );
	bColor.push_back( 0.0f );
	bColor.push_back( 1.0f );

	assert( GL_NO_ERROR == glGetError() );

	glViewport( 0, 0, width, height );


	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );	
	glClear( GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	glPointSize( pointSize );

	glUseProgram( shader.getId() );

	glActiveTexture( GL_TEXTURE0 );
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_1D, texture );
	const int loc = glGetUniformLocation( shader.getId(), "tex" );
	if( loc >= 0 ) {
		glUniform1i( loc, 0 );
	}
	else {
		assert( false );
	}

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

	ShaderUtil::setUniformMatrix( shader.getId(), "projectionMatrix", perspectiveMatrix );
	ShaderUtil::setUniformMatrix( shader.getId(), "modelviewMatrix", camera->getModelviewMatrix() );
	ShaderUtil::setUniform( shader.getId(), "min", min );
	ShaderUtil::setUniform( shader.getId(), "max", max );

	glVertexAttribPointer( positionLocation, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()) );
	glVertexAttribPointer( valueLocation, 1, GL_FLOAT, GL_FALSE, 0, &( values.front() ) );
	
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	glDrawArrays( GL_POINTS, 0, positions.size() / 3 );
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	
	glBindFragDataLocation( shader.getId(), 0, "fragColor" );

	glDeleteTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_1D, 0 );

	glUseProgram( 0 );


	assert( GL_NO_ERROR == glGetError() );
}