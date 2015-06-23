#define _CRT_SECURE_NO_WARNINGS

#include "SmoothRenderer.h"

#include "../Graphics/Material.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;


void SmoothRenderer::build()
{
	Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"in vec3 normal;					\n"
		"out vec3 vColor;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"uniform vec3 lightPosition;		\n"
		"uniform vec3 eyePosition;			\n"
		"void main(void)					\n"
		"{\n"
		"	vec3 n = normalize( normal );	\n"
		"	vec3 s = normalize( lightPosition - eyePosition );						\n"
		"   vec3 diffuseColor = max(dot(s, n), 0.0) * vec3(0.0, 0.0, 1.0);		\n"
		"   vec3 ambientColor = vec3( 0.2, 0.2, 0.2); \n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );	\n"
		"	vColor = diffuseColor + ambientColor;				\n"
		"}\n"
		;

	vShader.compile( vStr, Shader::Stage::VERTEX );

	const std::string fStr =
		"#version 150						\n"
		"in vec3 vColor;					\n"
		"out vec4 fragColor;				\n"
		"void main(void)											\n"
		"{															\n"
		"	fragColor = vec4( vColor, 1.0);					\n"
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

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.normal = glGetAttribLocation(shader.getId(), "normal");

	return location;
}

void SmoothRenderer::render(const int width, const int height, const Camera<float>& camera, const TriangleBuffer<float>& buffer)
{
	const std::vector<float>& positions = buffer.getPositions();
	const std::vector<float>& normals = buffer.getNormals();
	const std::vector<float>& projectionMatrix = camera.getPerspectiveMatrix().toArray4x4();
	const std::vector<float>& modelviewMatrix = camera.getModelviewMatrix().toArray4x4();
	const std::vector<float>& eyePos = camera.getPos().toArray();

	glViewport(0, 0, width, height);

	const Location& location = getLocations();


	if ( positions.empty() ) {
		return;
	}

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());

	const std::vector< float > lightPos = { 10.0f, 10.0f, 10.0f };

	const GLint lightLoc = glGetUniformLocation(shader.getId(), "lightPosition");
	glUniform3fv( lightLoc, 1, &(lightPos.front() ) );


	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));
	glUniform3fv(location.eyePos, 1, &(eyePos.front()) );


	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribPointer(location.normal, 3, GL_FLOAT, GL_FALSE, 0, &(normals.front()));
	//glVertexAttribPointer(location.)

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, positions.size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);
}