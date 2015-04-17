#include "stdafx.h"
#include "ParticleRenderer.h"

#include <cassert>

#include "../Math/Vector3d.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ParticleRenderer::ParticleRenderer()
{}

ParticleRenderer::~ParticleRenderer()
{
}

namespace {
	GLuint positionLocation = 0;
	GLuint idLocation = 1;
}
static std::stringstream getVertexSource()
{
	std::stringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in int id;" << std::endl
		<< "out vec3 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform int objectId;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );" << std::endl
		<< "	float r = id / 1024.0;" << std::endl
		<< "	float g = id / 2048.0;" << std::endl
		<< "	float b = objectId / 512.0;" << std::endl
		<< "	vColor = vec3( r, g, b);" << std::endl
		<< "}" << std::endl;
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
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream;
}

void ParticleRenderer::build()
{
	Graphics::Shader vShader;
	Graphics::Shader fShader;
	vShader.compile(getVertexSource().str(), Graphics::Shader::Stage::VERTEX);
	fShader.compile(getFragmentSource().str(), Graphics::Shader::Stage::FRAGMENT);
	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader);

	//glBindAttribLocation(shader.getId(), positionLocation, "position");
	//glBindAttribLocation(shader.getId(), idLocation, "id");

	positionLocation = glGetAttribLocation(shader.getId(), "position");
	idLocation = glGetAttribLocation(shader.getId(), "id");
}

void ParticleRenderer::render(const int width, const int height, const Camera<float>* camera, const std::vector<float>& positions, const std::vector<unsigned int>& ids)
{
	if (positions.empty()) {
		return;
	}

	const Matrix4d<float>& perspectiveMatrix = camera->getPerspectiveMatrix();
	const Matrix4d<float>& modelviewMatrix = camera->getModelviewMatrix();

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());

	glBindFragDataLocation(shader.getId(), 0, "fragColor");


	ShaderUtil::setUniformMatrix(shader.getId(), "projectionMatrix", perspectiveMatrix);
	ShaderUtil::setUniformMatrix(shader.getId(), "modelviewMatrix", modelviewMatrix);
	ShaderUtil::setUniform(shader.getId(), "objectId", 0);

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribIPointer(idLocation, 1, GL_INT, 0, &(ids.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);

	assert(GL_NO_ERROR == glGetError());
}