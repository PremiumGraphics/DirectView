#ifndef __CRYSTAL_GRAPHICS_LIGHT_H__
#define __CRYSTAL_GRAPHICS_LIGHT_H__

#include "ColorRGB.h"
#include "../Math/Vector3d.h"

#include <list>
#include <string>

namespace Crystal {
	namespace Graphics {

class Light {
public:
	Light() :
		pos( Math::Vector3d( 1.0f, 1.0f, 1.0f ) ),
		diffuse( ColorRGB<float>::Red() ),
		specular( ColorRGB<float>::Green() ),
		ambient( ColorRGB<float>::Blue() ),
		isSelected( true )
	{
	}

	~Light(){};

public:

	Graphics::ColorRGB<float> getAmbient() const { return ambient; }

	void setAmbient( const Graphics::ColorRGB<float>& a ) { this->ambient = a; }

	Graphics::ColorRGB<float> getDiffuse() const { return diffuse; }

	void setDiffuse( const Graphics::ColorRGB<float>& d ) { this->diffuse = d; }

	Graphics::ColorRGB<float> getSpecular() const { return specular; }

	void setSpecular( const Graphics::ColorRGB<float> s ) { this->specular = s; }

	std::string name;
	Math::Vector3d pos;
	bool isSelected;

private:
	Graphics::ColorRGB<float> ambient;
	Graphics::ColorRGB<float> diffuse;
	Graphics::ColorRGB<float> specular;
};

	}
}

#endif