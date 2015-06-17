#include "PointRenderer.h"

#include <cassert>

#include "../Math/Vector.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

PointRenderer::PointRenderer()
{}

PointRenderer::~PointRenderer()
{
}

namespace {
	GLuint positionLocation = 0;

	static std::stringstream getVertexSource()
	{
		std::stringstream stream;
		stream
			<< "#version 150" << std::endl
			<< "in vec3 position;" << std::endl
			<< "out vec3 vColor;" << std::endl
			<< "uniform mat4 projectionMatrix;" << std::endl
			<< "uniform mat4 modelviewMatrix;" << std::endl
			<< "void main(void)" << std::endl
			<< "{" << std::endl
			<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );" << std::endl
			<< "	vColor = vec3( 0.0, 0.0, 1.0);" << std::endl
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

}

void PointRenderer::build()
{
	Graphics::Shader vShader;
	Graphics::Shader fShader;
	vShader.compile(getVertexSource().str(), Graphics::Shader::Stage::VERTEX);
	fShader.compile(getFragmentSource().str(), Graphics::Shader::Stage::FRAGMENT);
	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader);

	glBindAttribLocation(shader.getId(), positionLocation, "position");
}

void PointRenderer::render(const int width, const int height, const Camera<float>* camera)
{
	if (points.empty()) {
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

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, &(points.front()));

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, points.size() / 3);

	glDisableVertexAttribArray(0);

	glUseProgram(0);


	assert(GL_NO_ERROR == glGetError());
}