//#include "stdafx.h"
#include "MTLFile.h"

#include "Helper.h"

#include <vector>

#include <cassert>

#include <string>

#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"


using namespace Crystal::Graphics;
using namespace Crystal::IO;

bool MTLFile::read(const std::string& filename)
{
	std::ifstream stream;

	stream.open(filename.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool MTLFile::read(std::istream& stream)
{
	std::string str;
	
	std::string comment;

	//Material* material = nullptr;

	std::string header= Helper::read< std::string >(stream);

	while( !stream.eof() ) {
		if( header.front() == '#' ) {
			std::getline( stream, header );
			//comment += header;
		}
		else if( header == "newmtl" ) {
			const std::string& materialName = Helper::read< std::string >(stream);
			
			MTL mtl;
			mtl.name = materialName;
			mtls.push_back( mtl );
		}
		else if( header == "Ka" ) {
			mtls.back().ambient = Helper::readColorRGB(stream);

		}
		else if( header == "Kd" ) {
			mtls.back().diffuse = Helper::readColorRGB(stream);
		}
		else if( header == "Ks" ) {
			mtls.back().specular = Helper::readColorRGB(stream);
		}
		else if( header == "Ns" ) {
			const float ns = Helper::read< float >( stream );
		}
		else if( header == "map_Ka" ) {
			mtls.back().ambientTexture = Helper::read< std::string >(stream);
		}
		else if( header == "map_Kd" ) {
			str = Helper::read< std::string >(stream);
			if( str == "-o" ) {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			if( str == "-s" ) {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			mtls.back().diffuseTexture = str;
		}
		else if( header == "map_Ks" ) {
			const std::string& filename = Helper::read< std::string >(stream);
			mtls.back().shininessTexture = filename;
		}
		else if( header == "map_Ns" ) {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if( header == "map_d" ) {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if ( header == "map_bump" || header == "bump" ) {
			mtls.back().bumpTexture = Helper::read< std::string >(stream);
		}

		stream >> header;
	}

	return true;
}

bool MTLFile::save( const std::string& filename )
{
	std::ofstream stream( filename.c_str() );

	if( !stream.is_open() ) {
		return false;
	}

	stream << "# Exported from CGStudio" << std::endl;

	//for( const Material* m : materials.getMaterials() ) {
	//	stream << std::endl;

	//	stream << "newmtl " << m->name << std::endl;

	//	const ColorRGBA<float>& ambient = m->getAmbient();
	//	stream << "Ka " << ambient.getRed() << " " << ambient.getGreen() << " " << ambient.getBlue() << std::endl;

	//	const ColorRGBA<float>& diffuse = m->getDiffuse();
	//	stream << "Kd " << diffuse.getRed() << " " << diffuse.getGreen() << " " << diffuse.getBlue() << std::endl;

	//	const ColorRGBA<float>& specular = m->getSpecular();
	//	stream << "Ks " << specular.getRed() << " " << specular.getGreen() << " " << specular.getBlue() << std::endl;

	//	//stream << "Ns " << m->shininess << std::endl;

	//	/*
	//	const Texture& texture = m->texture;
	//	if( !texture.getAmbientFileName().empty() ) {
	//		stream << "map_Ka " << texture.getAmbientFileName() << std::endl;
	//	}
	//	if( !texture.getDiffuseFileName().empty() ) {
	//		stream << "map_Kd " << texture.getDiffuseFileName() << std::endl;
	//	}
	//	if( !texture.getSpecularFileName().empty() ) {
	//		stream << "map_Ks " << texture.getSpecularFileName() << std::endl;
	//	}
	//	*/
	//}
	return true;
}