#include "VolumeRenderer.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void VolumeRenderer::build()
{
	Graphics::Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"in int id;							\n"
		"in float density;					\n"
		"out vec4 color;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );\n"
		"	color.r = (density <0) ? 1 : 0;		\n"
		"	color.g = 0.0;			\n"
		"	color.b = (density >0) ? 1 : 0;					\n"
		"	color.a = abs(density);		\n"
		"}\n"
		;

	vShader.compile(vStr, Graphics::Shader::Stage::VERTEX);

	Graphics::Shader fShader;

	const std::string fStr =
		"#version 150			\n"
		"in vec4 color;			\n"
		"out vec4 fragColor;	\n"
		"void main(void)		\n"
		"{\n"
		"	fragColor = color;//color;	\n"
		"}						\n"
		;

	fShader.compile(fStr, Graphics::Shader::Stage::FRAGMENT);

	shader.link(vShader, fShader);

	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader);

}

VolumeRenderer::Location VolumeRenderer::getLocations()
{
	VolumeRenderer::Location location;

	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.density = glGetAttribLocation(shader.getId(), "density");

	return location;
}


void VolumeRenderer::render(const int width, const int height, const Camera<float>& camera, const VolumeBuffer<float>& buffer)
{
	const auto& positions = buffer.getPositions();
	const auto& densities = buffer.getValues();

	if (positions.empty()){
		return;
	}

	const std::vector<float>& projectionMatrix = camera.getPerspectiveMatrix().toArray4x4();
	const std::vector<float>& modelviewMatrix = camera.getModelviewMatrix().toArray4x4();

	//assert(GL_NO_ERROR == glGetError());
	const auto error = glGetError();
	if (error != GL_NO_ERROR) {
		assert(false);
		//G glGetString(error);

	}

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());

	const Location& location = getLocations();

	assert(GL_NO_ERROR == glGetError());


	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribPointer(location.density, 1, GL_FLOAT, GL_FALSE, 0, &(densities.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	assert(GL_NO_ERROR == glGetError());

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	assert(GL_NO_ERROR == glGetError());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

	assert(GL_NO_ERROR == glGetError());

}