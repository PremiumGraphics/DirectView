#ifndef __CRYSTAL_IO_MTL_FILE_H__
#define __CRYSTAL_IO_MTL_FILE_H__

#include <map>

#include "../Graphics/Material.h"

#include "../Math/Vector3d.h"

#include "../Graphics/ColorRGB.h"


#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

struct MTLTextureOption {
	bool blendu;
	bool blendv;
	float boost;
	float baseValue;
	float gainValue;
	Math::Vector3d origin;
	Math::Vector3d scale;
	Math::Vector3d turblence;
	int resolution;
	bool clamp;
	float bm;
	char imfchan;
};


struct MTL {
	std::string name;
	Graphics::ColorRGB<float> ambient;
	Graphics::ColorRGB<float> diffuse;
	Graphics::ColorRGB<float> specular;
	std::string ambientTexture;
	std::string diffuseTexture;
	std::string bumpTexture;
	std::string shininessTexture;
	int illumination;

	bool operator==(const MTL& rhs) const {
		return
			name == rhs.name &&
			ambient == rhs.ambient &&
			diffuse == rhs.diffuse &&
			specular == rhs.specular &&
			ambientTexture == rhs.ambientTexture &&
			diffuseTexture == rhs.diffuseTexture &&
			bumpTexture == rhs.bumpTexture &&
			shininessTexture == rhs.shininessTexture &&
			illumination == rhs.illumination;
	}
};

class MTLFile {
public:
	bool read( const std::string& filename );

	bool read(std::istream& stream);

	bool save( const std::string& filename );

	std::vector<MTL> getMaterials() const { return mtls; }

private:
	std::vector<MTL> mtls;
};

	}
}

#endif