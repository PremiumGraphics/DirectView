#ifndef __CRYSTAL_SHADER_SHADER_OBJECT_H__
#define __CRYSTAL_SHADER_SHADER_OBJECT_H__


#include "GLee.h"

#include <vector>
#include <string>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"


#include <string>

namespace Crystal {
	namespace Shader {

class ShaderUnit
{
public:
	ShaderUnit(void);
	
	~ShaderUnit(void);

	enum class Stage {
		VERTEX,
		FRAGMENT,
		GEOMETRY,
	};

	bool compile( const std::string& source, const ShaderUnit::Stage stage );

	void clear();

	unsigned int getID() const { return id; }

	std::string getLog() const { return log; }

private:

	unsigned int id;

	std::string log;
};


class ShaderObject
{
public:
	ShaderObject(void);

	~ShaderObject(void);

	void clear();

	void link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader );

	void link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader, const ShaderUnit& geometryShader );

	std::string getLog() const { return log; }

	unsigned int getId() const { return id; }

public:
	unsigned int id;

	std::string log;
};

class ShaderUtil
{
public:
	static void setUniform( const int id, const std::string& name, const int value );

	static void setUniform( const int id, const std::string& name, const float value );

	static void setUniformVector( const int id, const std::string& name, GLfloat *value );

	static void setUniformVector( const int id, const std::string& name, const std::vector< GLfloat >& value );

	static void setUniformMatrix( const int id, const std::string& name, const Math::Matrix4d< float >& matrix );

	static void setUniformMatrix( unsigned int location, const Math::Matrix4d< float >& matrix );

private:
	static bool isValidUniform(const std::string& name, GLuint location);

};

	}
}

#endif