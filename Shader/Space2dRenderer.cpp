#include "Space2dRenderer.h"

#include <cassert>

#include "../Math/Vector3d.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

Space2dRenderer::Space2dRenderer()
{
}

Space2dRenderer::~Space2dRenderer()
{
}

namespace {
	GLuint positionLocation = 0;
}

static std::stringstream getVertexSource()
{
	std::stringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "out vec3 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform sampler2D tex;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );" << std::endl
		<< "	vec2 texCoord = vec2(0.0, 0.0);" << std::endl
		<< "	vColor = texture( tex, texCoord ).rgb;" << std::endl
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

void Space2dRenderer::build()
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

void Space2dRenderer::render(const int width, const int height, const Camera<float>* camera, const std::vector<float>& positions)
{
	const Matrix4d<float>& perspectiveMatrix = camera->getPerspectiveMatrix();

	std::vector< float > bColor;
	bColor.push_back(0.0f);
	bColor.push_back(0.0f);
	bColor.push_back(1.0f);

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glActiveTexture(GL_TEXTURE0);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	const int loc = glGetUniformLocation(shader.getId(), "tex");
	if (loc >= 0) {
		glUniform1i(loc, 0);
	}
	else {
		assert(false);
	}

	const std::vector<float> t{ 0.0f, 0.0f, 0.0f, 0.0f };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, &(t.front()));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ShaderUtil::setUniformMatrix(shader.getId(), "projectionMatrix", perspectiveMatrix);
	ShaderUtil::setUniformMatrix(shader.getId(), "modelviewMatrix", camera->getModelviewMatrix());

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POLYGON, 0, positions.size() / 3);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDeleteTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);


	assert(GL_NO_ERROR == glGetError());
}