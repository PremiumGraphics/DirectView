#ifndef __CRYSTAL_GRAPHICS_LIGHT_H__
#define __CRYSTAL_GRAPHICS_LIGHT_H__

#include "ColorRGB.h"
#include "../Math/Vector3d.h"

#include <list>
#include <string>
#include <memory>

namespace Crystal {
	namespace Graphics {


class PointLight {
public:
	PointLight() :
		pos( Math::Vector3d( 1.0f, 1.0f, 1.0f ) ),
		diffuse( ColorRGB<float>::Red() ),
		specular( ColorRGB<float>::Green() ),
		isSelected( true )
	{
	}

	~PointLight(){};

public:


	Graphics::ColorRGB<float> getDiffuse() const { return diffuse; }

	void setDiffuse( const Graphics::ColorRGB<float>& d ) { this->diffuse = d; }

	Graphics::ColorRGB<float> getSpecular() const { return specular; }

	void setSpecular( const Graphics::ColorRGB<float> s ) { this->specular = s; }

	Math::Vector3d getPos() const { return pos; }

	void setPos(const Math::Vector3d& pos) { this->pos = pos; }

	void setName(const std::string& name) { this->name = name; }

	std::string name;
	bool isSelected;

private:
	Math::Vector3d pos;

	Graphics::ColorRGB<float> diffuse;
	Graphics::ColorRGB<float> specular;
};

typedef std::shared_ptr< PointLight > LightSPtr;
typedef std::list < LightSPtr > LightSPtrList;

class DirectionalLight {
public:
	DirectionalLight() :
		color(ColorRGB<float>::White())
	{}

	void setDirection(const Math::Vector3d& direction) { this->direction = direction; }

	Math::Vector3d getDirection() const { return direction; }

	Graphics::ColorRGB<float> getColor() const { return color; }

	void setColor(const Graphics::ColorRGB<float>& a) { this->color = a; }

private:
	Math::Vector3d direction;

	Graphics::ColorRGB<float> color;
};

class AmbientLight {
public:
	AmbientLight() :
		color( ColorRGB<float>::White() )
	{}
	
	Graphics::ColorRGB<float> getColor() const { return color; }

	void setColor(const Graphics::ColorRGB<float>& a) { this->color = a; }

private:
	Graphics::ColorRGB<float> color;
};

class LightBuilder
{
public:
	LightSPtr build() {
		LightSPtr l(new PointLight());
		lights.push_back(l);
		return l;
	}

	void clear(){ lights.clear(); }

	void remove(LightSPtr l) { lights.remove(l); }

	LightSPtrList getLights() const { return lights; }


private:
	LightSPtrList lights;
};

typedef std::shared_ptr< LightBuilder > LightBuilderSPtr;

	}
}

#endif