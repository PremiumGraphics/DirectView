#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

#include "SmoothRenderer.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;


SmoothRenderer::SmoothRenderer()
{
}

SmoothRenderer::~SmoothRenderer()
{
}

void SmoothRenderer::build()
{
	Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"in vec3 normal;					\n"
		"out vec3 vNormal;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );	\n"
		"	vNormal = normal;				\n"
		"}\n"
		;

	vShader.compile( vStr, Shader::Stage::VERTEX );

	const std::string fStr =
		"#version 150						\n"
		"uniform vec3 lightIntensity;		\n"
		"in vec3 vPosition;					\n"
		"in vec3 vNormal;					\n"
		"out vec4 fragColor;				\n"
		"uniform vec3 eyePosition;			\n"
		"struct Light{						\n"
		"	vec3 position;					\n"
		"	vec3 Kd;						\n"
		"	vec3 Ka;						\n"
		"	vec3 Ks;						\n"
		"};									\n"
		"uniform Light lights[8];			\n"
		"struct Material{					\n"
		"	vec3 ambient;					\n"
		"	vec3 diffuse;					\n"
		"	vec3 specular;					\n"
		"	float shininess;				\n"
		"};									\n"
		"uniform Material material;			\n"
		"uniform int lightSize;				\n"
		"vec3 ads(int i)							\n"
		"{									\n"
		"	vec3 n = normalize( vNormal );	\n"
		"	vec3 s = normalize( lights[i].position - eyePosition );						\n"
		"	vec3 v = normalize( vec3( -eyePosition) );				\n;"
		"	vec3 r = reflect( -s, n );			\n"
		"	return													\n"
		"		lightIntensity *									\n"
		"			(lights[i].Ka * material.ambient +											\n"
		"			 lights[i].Kd * max( dot( s, n ), 0.0 ) * material.diffuse +				\n"
		"			 lights[i].Ks * pow ( max ( dot( r, v ), 0.0 ), material.shininess ) * material.specular	\n"
		"			);												\n"
		"}															\n"
		"void main(void)											\n"
		"{															\n"
		"	vec4 c = vec4( 0.0, 0.0, 0.0, 0.0);													\n"
		"	for( int i = 0; i < lightSize; ++i ) {					\n"
		"		c += vec4( ads(i), 1.0 );							\n"
		"	}														\n"
		"	fragColor = c;					\n"
		"}															\n"
		;

	Shader fShader;
	fShader.compile( fStr, Shader::Stage::FRAGMENT );

	shader.link( vShader, fShader );
}

SmoothRenderer::Location SmoothRenderer::getLocations()
{
	Location location;

	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");
	location.eyePos = glGetUniformLocation(shader.getId(), "eyePosition");

	location.matAmbient = glGetUniformLocation(shader.getId(), "material.ambient");
	location.matSpecular = glGetUniformLocation(shader.getId(), "material.specular");
	location.matDiffuse = glGetUniformLocation(shader.getId(), "material.diffse");
	location.shininess = glGetUniformLocation(shader.getId(), "material.shininess");

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.normal = glGetAttribLocation(shader.getId(), "normal");

	return location;
}

void SmoothRenderer::render(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices )
{	
	glViewport( 0, 0, width, height );

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );	
	glClear( GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	const Location& location = getLocations();


	if ( param.positions.empty() || indices.empty()) {
		return;
	}

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());



	int i = 0;
	for (Light* l : param.lights) {
		const std::vector< float >& lightPos = l->pos.toArray();
		const std::vector< float >& kd = l->getDiffuse().toArray3();
		const std::vector< float >& ka = l->getAmbient().toArray3();
		const std::vector< float >& ks = l->getSpecular().toArray3();

		char str[256];
		sprintf(str, "lights[%d].position", i);
		const GLint lightLoc = glGetUniformLocation(shader.getId(), str);
		glUniform3fv( lightLoc, 1, &(lightPos.front() ) );

		sprintf(str, "lights[%d].Kd", i);
		const GLuint kdLoc = glGetUniformLocation(shader.getId(), str);
		glUniform3fv(kdLoc, 1, &(kd.front()));

		sprintf(str, "lights[%d].Ka", i);
		const GLuint kaLoc = glGetUniformLocation(shader.getId(), str);
		glUniform3fv(kaLoc, 1, &(ka.front()));

		sprintf(str, "lights[%d].Ks", i);
		const GLuint ksLoc = glGetUniformLocation(shader.getId(), str);
		glUniform3fv(ksLoc, 1, &(ks.front()));
		++i;
	}


	//shader.setUniformVector("lightIntensity", ColorRGBA<float>::White().toArray3());

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(param.projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(param.modelviewMatrix.front()));
	glUniform3fv(location.eyePos, 1, &(param.eyePos.front()) );

	{
		const GLenum error = glGetError();
		assert(GL_NO_ERROR == error);
	}


	glUniform3fv(location.matAmbient, 1, &(param.matAmbient.front()));
	glUniform3fv(location.matDiffuse, 1, &(param.matDiffuse.front()));
	glUniform3fv(location.matSpecular, 1, &(param.matSpecular.front()) );
	glUniform1f(location.shininess, param.shininess);
	//glUniform3fv( location.matAmbient, 1, m)

	{
		const GLenum error = glGetError();
		assert(GL_NO_ERROR == error);
	}


	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(param.positions.front()));
	glVertexAttribPointer(location.normal, 3, GL_FLOAT, GL_FALSE, 0, &(param.normals.front()));

	{
		const GLenum error = glGetError();
		assert(GL_NO_ERROR == error);
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	for (size_t i = 0; i < indices.size(); ++i) {
		const std::vector<unsigned int>& is = indices[i];
		glDrawElements(GL_POLYGON, is.size(), GL_UNSIGNED_INT, &(is.front()));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);

	/*	
	for( Graphics::Polygon* model : polygon->getPolygons() ) {
			shader.setUniformVector( "material.ambient", model->material->getAmbient().toArray3() );
			shader.setUniformVector( "material.diffuse", model->material->getDiffuse().toArray3() );
			shader.setUniformVector( "material.specular", model->material->getSpecular().toArray3() );
			shader.setUniform( "material.shininess", model->material->getShininess() );
	
		}
	}
	
	*/
}