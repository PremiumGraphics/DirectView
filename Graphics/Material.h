#ifndef __CRYSTAL_GRAPHICS_MATERIAL_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_H__

#include <list>
#include <string>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

struct Texture
{
	std::string ambient;
	std::string diffuse;
	std::string bump;
	std::string shininess;
};

class Material
{
public:
	Material():
		diffuse(Graphics::ColorRGBA<float>::Black()),
		specular(Graphics::ColorRGBA<float>::Black()),
		ambient(Graphics::ColorRGBA<float>::Black()),
		shininess(1.0f)
	{}

	Material(const int id) :
		diffuse( Graphics::ColorRGBA<float>::Black() ),
		specular( Graphics::ColorRGBA<float>::Black() ),
		ambient( Graphics::ColorRGBA<float>::Black() ),
		shininess( 1.0f )
	{
	}

	~Material()
	{}

public:

	std::string getName() const { return name;  }

	void setName(const std::string& name) { this->name = name; }

	void setAmbient( const Graphics::ColorRGBA<float>& a ) { this->ambient = a; }

	Graphics::ColorRGBA<float> getAmbient() const { return ambient; }

	void setDiffuse( const Graphics::ColorRGBA<float>& d ) { this->diffuse = d; }

	Graphics::ColorRGBA<float> getDiffuse() const { return diffuse; }

	void setSpecular( const Graphics::ColorRGBA<float>& s ) { this->specular = s; }

	Graphics::ColorRGBA<float> getSpecular() const { return specular; }

	void setShininess( const float s ) { this->shininess = s; }

	float getShininess() const { return shininess; }

	Texture getTexture() const { return texture; }

	void setTexture(const Texture& texture) { this->texture = texture; }

private:
	std::string name;

	float shininess;
	Graphics::ColorRGBA<float> ambient;
	Graphics::ColorRGBA<float> diffuse;
	Graphics::ColorRGBA<float> specular;

	Texture texture;

};

	}
}


#endif