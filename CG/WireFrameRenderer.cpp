#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS

#include "WireFrameRenderer.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;

WireFrameRenderer::WireFrameRenderer()
{
}

WireFrameRenderer::~WireFrameRenderer()
{
}

void WireFrameRenderer::build()
{
	Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );\n"
		"}\n"
		;

	vShader.compile( vStr, Shader::Stage::VERTEX );

	Shader fShader;

	const std::string fStr =
		"#version 150			\n"
		"//uniform vec3 color;	\n"
		"out vec4 fragColor;	\n"
		"void main(void)		\n"
		"{\n"
		"	fragColor.rgb = vec3( 0.5, 0.5, 0.5 );//color;	\n"
		"	fragColor.a = 1.0;	\n"
		"}						\n"
		;

	fShader.compile( fStr, Shader::Stage::FRAGMENT );

	shader.link( vShader, fShader );

	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader);

}

WireFrameRenderer::Location WireFrameRenderer::getLocations()
{
	WireFrameRenderer::Location location;

	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader.getId(), "position");

	return location;
}


void WireFrameRenderer::render(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());


	const Location& location = getLocations();

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(param.projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(param.modelviewMatrix.front()));

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(param.positions.front()));

	glEnableVertexAttribArray(0);

	for (size_t i = 0; i < indices.size(); ++i) {
		const std::vector<unsigned int>& is = indices[i];
		glDrawElements(GL_LINE_LOOP, is.size(), GL_UNSIGNED_INT, &(is.front()));
	}
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);
}