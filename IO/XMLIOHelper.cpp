#include "XMLIOHelper.h"

#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;
using namespace tinyxml2;

Vector3d XMLIOHelper::readVector3d( XMLElement* element )
{
	const float x = element->FloatAttribute( "x" );
	const float y = element->FloatAttribute( "y" );
	const float z = element->FloatAttribute( "z" );

	return Vector3d( x, y, z );
}

void XMLIOHelper::save( XMLElement* element, const Vector3d& vector )
{
	element->SetAttribute( "x", vector.getX() );
	element->SetAttribute( "y", vector.getY() );
	element->SetAttribute( "z", vector.getZ() );
}

int XMLIOHelper::readInt( XMLElement* element )
{
	return element->IntAttribute( "v"  );
}

void XMLIOHelper::save( XMLElement* element,  const int value )
{
	element->SetAttribute( "v", value );
}

float XMLIOHelper::readFloat( XMLElement* element )
{
	return element->FloatAttribute( "v" );
}

ColorRGBA<float> XMLIOHelper::readColor( XMLElement* element )
{
	const float red = element->FloatAttribute( "r" );
	const float green = element->FloatAttribute( "g" );
	const float blue = element->FloatAttribute( "b" );

	return ColorRGBA<float>( red, green, blue, 1.0 );
}

void XMLIOHelper::save( tinyxml2::XMLElement* element, const ColorRGB<float>& color )
{
	element->SetAttribute( "r", color.getRed() );
	element->SetAttribute( "g", color.getGreen() );
	element->SetAttribute( "b", color.getBlue() );
}


void XMLIOHelper::save( tinyxml2::XMLElement* element, const ColorRGBA<float>& color )
{
	element->SetAttribute( "r", color.getRed() );
	element->SetAttribute( "g", color.getGreen() );
	element->SetAttribute( "b", color.getBlue() );
}


void XMLIOHelper::save( XMLElement* element, const float value )
{
	element->SetAttribute( "v", value );
}
