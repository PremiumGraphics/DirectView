#include "WireFrameRenderer.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

WireFrameRenderer::~WireFrameRenderer()
{
}

void WireFrameRenderer::build()
{
	Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"in vec3 color;						\n"
		"out vec3 vColor;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );\n"
		"	vColor = color;					\n"
		"}\n"
		;

	vShader.compile( vStr, Shader::Stage::VERTEX );

	Shader fShader;

	const std::string fStr =
		"#version 150			\n"
		"in vec3 vColor;	\n"
		"out vec4 fragColor;	\n"
		"void main(void)		\n"
		"{\n"
		"	fragColor.rgb = vColor;//color;	\n"
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
	location.color = glGetAttribLocation(shader.getId(), "color");

	return location;
}


void WireFrameRenderer::render(const int width, const int height, const Camera<float>& camera, const DisplayList& list)
{
	const std::vector<float> positions = list.getPositions();
	const std::vector< std::vector<unsigned int> > ids = list.getIds();
	const std::vector<float> colors = list.getColors();
	if ( positions.empty() ) {
		return;
	}

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());

	const std::vector<float>& projectionMatrix = camera.getPerspectiveMatrix().toArray4x4();
	const std::vector<float>& modelviewMatrix = camera.getModelviewMatrix().toArray4x4();

	const Location& location = getLocations();

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribPointer(location.color, 3, GL_FLOAT, GL_FALSE, 0, &(colors.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	for ( const std::vector<unsigned int>& ids_ : ids ) {
		glDrawElements(GL_LINE_LOOP, ids_.size(), GL_UNSIGNED_INT, &(ids_.front()));
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);
}