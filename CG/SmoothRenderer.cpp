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

#include "../Converter.h"

void SmoothRenderer::render(const int width, const int height, Model* model )
{	
	Camera<float>* camera = model->getCamera();
	PolygonCollection* polygon = model->getPolygonModel();

	const Matrix4d<float>& perspectiveMatrix = camera->getPerspectiveMatrix();

	assert( GL_NO_ERROR == glGetError() );

	glViewport( 0, 0, width, height );

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );	
	glClear( GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	const std::vector< float >& eyePos = camera->getPos().toArray();

	shader.apply();
	shader.setUniformMatrix( "projectionMatrix", perspectiveMatrix );
	shader.setUniformMatrix( "modelviewMatrix", camera->getModelviewMatrix() );
	shader.setUniformVector( "eyePosition", eyePos );

	const LightList& lights = model->getLightModel()->getSelectedLights();
	shader.setUniform( "lightSize", (int)lights.size() );

	int i = 0;
	for( Light* l : lights ) {
		const std::vector< float >& lightPos = l->pos.toArray();
		const std::vector< float >& kd = l->getDiffuse().toArray3();
		const std::vector< float >& ka = l->getAmbient().toArray3();
		const std::vector< float >& ks = l->getSpecular().toArray3();

		char str[256];
		sprintf( str, "lights[%d].position", i );
		shader.setUniformVector( str, lightPos );
		sprintf( str, "lights[%d].Kd", i );
		shader.setUniformVector( str, kd );
		sprintf( str, "lights[%d].Ka", i );
		shader.setUniformVector( str, ka );
		sprintf( str, "lights[%d].Ks", i );
		shader.setUniformVector( str, ks );
		++i;
	}

	shader.setUniformVector( "lightIntensity", ColorRGBA<float>::White().toArray3() );
	
	for( Graphics::Polygon* model : polygon->getPolygons() ) {
		const FaceVector& faces = model->getFaces();
		for( Face* f : faces ) {
			std::vector< float > positions;
			VertexVector vertices = f->getVertices();
			std::vector< float > normals;
			for( Vertex* v : vertices ) {
				const std::vector< float >& ps = v->position.toArray();
				positions.insert( positions.end(), ps.begin(), ps.end() );
				const std::vector< float >& n = v->normal.toArray();
				normals.insert( normals.end(), n.begin(), n.end() );
			}
			shader.setUniformVector( "material.ambient", model->material->getAmbient().toArray3() );
			shader.setUniformVector( "material.diffuse", model->material->getDiffuse().toArray3() );
			shader.setUniformVector( "material.specular", model->material->getSpecular().toArray3() );
			shader.setUniform( "material.shininess", model->material->getShininess() );
	
			shader.setVertexAttrib( "normal", normals, 3 );
			shader.setVertex( "position", positions );
			shader.drawPolygon( positions.size() / 3 );
		}
	}

	shader.bindFrag( "fragColor" );

	shader.release();
	
	assert( GL_NO_ERROR == glGetError() );
}