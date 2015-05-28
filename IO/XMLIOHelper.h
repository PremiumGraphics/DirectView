#ifndef __CRYSTAL_IO_XML_IO_HELPER_H__
#define __CRYSTAL_IO_XML_IO_HELPER_H__

#include "tinyxml2.h"

#include "../Math/Vector.h"

#include "../Graphics/ColorRGB.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace CG {

class XMLIOHelper {
public:
	static Math::Vector3d<float> XMLIOHelper::readVector3d( tinyxml2::XMLElement* element );

	static void save( tinyxml2::XMLElement* element, const Math::Vector3d<float>& vector );

	static int readInt( tinyxml2::XMLElement* element );

	static void save( tinyxml2::XMLElement* element, const int value );

	static float readFloat( tinyxml2::XMLElement* element );

	static void save( tinyxml2::XMLElement* element, const float value );

	static Graphics::ColorRGBA<float> readColor( tinyxml2::XMLElement* element );

	static void save( tinyxml2::XMLElement* element, const Graphics::ColorRGB<float>& color );

	static void save( tinyxml2::XMLElement* element, const Graphics::ColorRGBA<float>& color );

};

	}
}

#endif