#include "IDRenderer.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

IDRenderer::IDRenderer()
{
}

IDRenderer::~IDRenderer()
{
}

void IDRenderer::build()
{
	Graphics::Shader vShader;
	const std::string vStr =
		"#version 150						\n"
		"in vec3 position;					\n"
		"in int vertexId;			\n"
		"in int faceId;				\n"
		"in int polygonId;			\n"
		"out vec3 color;					\n"
		"uniform mat4 projectionMatrix;		\n"
		"uniform mat4 modelviewMatrix;		\n"
		"void main(void)					\n"
		"{\n"
		"	gl_Position = projectionMatrix * modelviewMatrix * vec4( position, 1.0 );\n"
		"	color.r = vertexId / 255.0;				\n"
		"	color.g = faceId / 255.0;					\n"
		"	color.b = polygonId / 255.0;					\n"
		"}\n"
		;

	vShader.compile(vStr, Graphics::Shader::Stage::VERTEX);

	Graphics::Shader fShader;

	const std::string fStr =
		"#version 150			\n"
		"in vec3 color;	\n"
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
	location.id = glGetAttribLocation(shader.getId(), "vertexId");
	location.faceId = glGetAttribLocation(shader.getId(), "faceId");
	location.polygonId = glGetAttribLocation(shader.getId(), "polygonId");

	return location;
}


void IDRenderer::render(const int width, const int height, const Camera<float>& camera, const DisplayList& list)
{
	if (list.getPositions().empty() ) {
		return;
	}

	const std::vector<float>& positions = list.getPositions();
	const std::vector< std::vector<unsigned int> >& ids = list.getIds();
	const std::vector<unsigned int>& vertexIds = list.getVertexIds();
	const std::vector<unsigned int>& faceIds = list.getFaceIds();
	const std::vector<unsigned int>& polygonIds = list.getPolygonIds();

	const std::vector<float>& projectionMatrix = camera.getPerspectiveMatrix().toArray4x4();
	const std::vector<float>& modelviewMatrix = camera.getModelviewMatrix().toArray4x4();

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);

	glUseProgram(shader.getId());

	const Location& location = getLocations();

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(vertexIds.front()) );
	glVertexAttribIPointer(location.faceId, 1, GL_INT, 0, &(faceIds.front()));
	glVertexAttribIPointer(location.polygonId, 1, GL_INT, 0, &(polygonIds.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	for (const std::vector<unsigned int>& ids_ : ids ) {
		glDrawElements(GL_POLYGON, ids_.size(), GL_UNSIGNED_INT, &(ids_.front()));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);
}