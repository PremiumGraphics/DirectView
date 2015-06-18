#include "IDRenderer.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void IDRenderer::build()
{
	Graphics::Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"in int type;						\n"
		"in int id;							\n"
		"in int isSelected;					\n"
		"out vec3 color;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );\n"
		"	color.r = type / 255.0;			\n"
		"	color.g = id / 255.0;			\n"
		"	color.b = isSelected;					\n"
		"}\n"
		;

	vShader.compile(vStr, Graphics::Shader::Stage::VERTEX);

	Graphics::Shader fShader;

	const std::string fStr =
		"#version 150			\n"
		"in vec3 color;			\n"
		"out vec4 fragColor;	\n"
		"void main(void)		\n"
		"{\n"
		"	fragColor.rgb = color;//color;	\n"
		"	fragColor.a = 1.0;	\n"
		"}						\n"
		;

	fShader.compile(fStr, Graphics::Shader::Stage::FRAGMENT);

	shader.link(vShader, fShader);

	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader);

}

IDRenderer::Location IDRenderer::getLocations()
{
	IDRenderer::Location location;

	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.type = glGetAttribLocation(shader.getId(), "type");
	location.id = glGetAttribLocation(shader.getId(), "id");
	location.isSelected = glGetAttribLocation(shader.getId(), "isSelected");
	//location.faceId = glGetAttribLocation(shader.getId(), "faceId");
	//location.polygonId = glGetAttribLocation(shader.getId(), "polygonId");

	return location;
}


void IDRenderer::render(const int width, const int height, const Camera<float>& camera, const Mode mode)
{
	if (positions.empty()) {
		return;
	}
	const std::vector<float>& projectionMatrix = camera.getPerspectiveMatrix().toArray4x4();
	const std::vector<float>& modelviewMatrix = camera.getModelviewMatrix().toArray4x4();

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());

	const Location& location = getLocations();

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribIPointer(location.type, 1, GL_INT, 0, &(types.front()) );
	glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(ids.front()) );
	glVertexAttribIPointer(location.isSelected, 1, GL_INT, 0, &(isSelecteds.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	if (mode == Mode::POINTS) {
		glDrawArrays(GL_POINTS, 0, positions.size() / 3);
	}
	else if (mode == Mode::LINES) {
		glDrawArrays(GL_LINES, 0, positions.size() / 3);
	}
	else if (mode == Mode::TRIANGLES) {
		glDrawArrays(GL_TRIANGLES, 0, positions.size() / 3);
	}
	else {
		assert(false);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);
}