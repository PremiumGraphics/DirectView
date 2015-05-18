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
	GLuint colorLocation = 1;
}
static std::stringstream getVertexSource()
{
	std::stringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 color;" << std::endl
		<< "out vec3 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );" << std::endl
		<< "	vColor = color;" << std::endl
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
	colorLocation = glGetAttribLocation(shader.getId(), "color");
}

void ParticleRenderer::render(const int width, const int height, const Camera<float>* camera, const ParticleDisplayList& list)
{
	const std::vector< float >& positions = list.getPositions();
	const std::vector< float >& colors = list.getColors();
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

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, &(colors.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);

	assert(GL_NO_ERROR == glGetError());
}