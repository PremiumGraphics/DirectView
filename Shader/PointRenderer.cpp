#include "PointRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void PointRenderer::build()
{
	Graphics::ShaderUnit vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		//		"in int id;							\n"
		"out vec3 color;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"uniform int isSelected;			\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );\n"
		"	color.r = isSelected;			\n"
		//"	color.g = id / 255.0;			\n"
		"	color.g = 0;					\n"
		"	color.b = 0;					\n"
		"}\n"
		;

	vShader.compile(vStr, Graphics::ShaderUnit::Stage::VERTEX);

	Graphics::ShaderUnit fShader;

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

	fShader.compile(fStr, Graphics::ShaderUnit::Stage::FRAGMENT);

	shader.link(vShader, fShader);

	std::string log;
	log += vShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader);

}

PointRenderer::Location PointRenderer::getLocations()
{
	Location location;

	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");
	location.isSelected = glGetUniformLocation(shader.getId(), "isSelected");

	location.position = glGetAttribLocation(shader.getId(), "position");

	return location;
}


void PointRenderer::render(const int width, const int height, const Camera<float>& camera, const PointBuffer<float>& buffer, const bool isSelected)
{

	const auto& positions = buffer.getPositions();

	if (positions.empty()) {
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

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));
	glUniform1i(location.isSelected, isSelected);

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	//glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(ids.front()));


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

}
