#include "stdafx.h"
#include "NormalRenderer.h"

#include <cassert>

#include "../Math/Vector3d.h"


#include "../Graphics/ShaderObject.h"
#include "../Graphics/Camera.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;

NormalRenderer::NormalRenderer()
{
}

NormalRenderer::~NormalRenderer()
{
}

namespace {
	GLint positionLocation;
	GLint vectorLocation;
	
	static std::stringstream getVVertexSource()
	{
		std::stringstream stream;
		stream
			<< "#version 150" << std::endl
			<< "in vec3 position;" << std::endl
			<< "in vec3 vector;" << std::endl
			<< "out vec3 vColor;" << std::endl
			<< "out vec3 vVector; " << std::endl
			<< "void main(void)" << std::endl
			<< "{" << std::endl
			<< "	gl_Position = vec4( position, 1.0 );" << std::endl
			<< "	vVector = vector;" << std::endl
			<< "	vColor = vec3( 0.0, 0.0, 1.0);" << std::endl
			<< "}" << std::endl;
		return stream;
	}

	static std::stringstream getVGeometrySource()
	{
		std::stringstream stream;
		stream
			<< "#version 150" << std::endl
			<< "layout( points ) in;" << std::endl
			<< "layout(line_strip, max_vertices = 2) out;" << std::endl
			//<< "layout( points, max_vertices = 1 ) out;" << std::endl
			<< "uniform mat4 projectionMatrix;" << std::endl
			<< "uniform mat4 modelviewMatrix;" << std::endl
			<< "uniform float scale;" << std::endl
			<< "in vec3 vColor[]; " << std::endl
			<< "in vec3 vVector[]; " << std::endl
			<< "out vec3 gColor; " << std::endl
			<< "void main()" << std::endl
			<< "{" << std::endl
			<< "	gl_Position = projectionMatrix * modelviewMatrix * gl_in[0].gl_Position;" << std::endl
			<< "	gColor = vColor[0];	" << std::endl
			<< "	EmitVertex();" << std::endl
			<< "	gl_Position = projectionMatrix * modelviewMatrix * ( gl_in[0].gl_Position + vec4( vVector[0], 0.0 ) * scale );" << std::endl
			<< "	gColor = vColor[0];	" << std::endl
			<< "	EmitVertex();" << std::endl
			<< "	EndPrimitive();	" << std::endl
			<< " }" << std::endl
			<< std::endl;
		return stream;
	}

	static std::stringstream getVFragmentSource()
	{
		std::stringstream stream;
		stream
			<< "#version 150" << std::endl
			<< "in vec3 gColor;" << std::endl
			<< "out vec4 fragColor;" << std::endl
			<< "void main(void)" << std::endl
			<< "{" << std::endl
			<< "	fragColor.rgb = gColor;" << std::endl
			<< "	fragColor.a = 1.0;" << std::endl
			<< "}" << std::endl;
		return stream;
	}

}

void NormalRenderer::build()
{
	const std::string& vStr = ::getVVertexSource().str();
	const std::string& gStr = ::getVGeometrySource().str();
	const std::string& fStr = ::getVFragmentSource().str();
	Shader vShader;
	Shader gShader;
	Shader fShader;
	vShader.compile(vStr, Shader::Stage::VERTEX);
	gShader.compile(gStr, Shader::Stage::GEOMETRY);
	fShader.compile(fStr, Shader::Stage::FRAGMENT);
	std::string log;
	log += vShader.getLog();
	log += gShader.getLog();
	log += fShader.getLog();
	shader.link(vShader, fShader, gShader);

	//positionLocation = glGetUniformLocation( shader.getId(), "position" );
}

void NormalRenderer::render(const int width, const int height, const Camera<float>* camera, const std::vector<float>& positions, const std::vector<float>& vectors )
{
	if (positions.empty()) {
		return;
	}
	if (vectors.empty())  {
		return;
	}

	const Matrix4d<float>& perspectiveMatrix = camera->getPerspectiveMatrix();

	assert(GL_NO_ERROR == glGetError());

	glViewport(0, 0, width, height);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glPointSize( pointSize );
	glLineWidth(1.0f);

	glUseProgram(shader.getId());

	ShaderUtil::setUniformMatrix(shader.getId(), "projectionMatrix", perspectiveMatrix);
	ShaderUtil::setUniformMatrix(shader.getId(), "modelviewMatrix", camera->getModelviewMatrix());

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	vectorLocation = glGetAttribLocation(shader.getId(), "vector");
	glVertexAttribPointer(vectorLocation, 3, GL_FLOAT, GL_FALSE, 0, &(vectors.front()));
	ShaderUtil::setUniform(shader.getId(), "scale", 1.0f);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_POINTS, 0, positions.size() / 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glBindTexture(GL_TEXTURE_1D, 0);

	glUseProgram(0);


	assert(GL_NO_ERROR == glGetError());
}