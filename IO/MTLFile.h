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
	MTLTextureOption()
	{
		setDefault();
	}

	void setDefault();

	void setBlendU(const bool u) { this->blendu = u; }

	bool getBlendU() const { return blendu; }

	void setBlendV(const bool v) { this->blendv = v; }

	bool getBlendV() const { return blendv; }

	void setBoost(const float b) { this->boost = b; }

	float getBoost() const { return boost; }

	void setBaseValue(const float v) { this->baseValue = v; }

	float getBaseValue() const { return baseValue; }

	void setGainValue(const float v) { this->gainValue = v; }

	float getGainValue() const { return gainValue; }

	void setOrigin(const Math::Vector3d& origin) { this->origin = origin; }

	Math::Vector3d getOrigin() const { return origin; }

	void setScale(const Math::Vector3d& scale) { this->scale = scale; }

	Math::Vector3d getScale() const { return scale; }

	void setTurblence(const Math::Vector3d& t) { this->turblence = t; }

	Math::Vector3d getTurblence() const { return turblence; }

	void setResolution(const int resolution) { this->resolution = resolution; }

	int getResolution() const { return resolution; }

	void setClamp(const bool clamp) { this->clamp = clamp; }

	bool getClamp() const { return clamp; }

	void setBumpMultiplier(const float bm) { this->bm = bm; }

	float getBumpMultiplier() const { return bm; }

	void setImfChan(const char imf) { this->imfchan = imf; }

	char getImfChan() const { return imfchan; }

private:
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

	static bool readOnOff(const std::string& str)
	{
		if (str == "on") {
			return true;
		}
		else if (str == "off") {
			return false;
		}
		else {
			assert(false);
			return false;
		}
	}


	static MTLTextureOption getTextureOptions(const std::string& str);


private:
	std::vector<MTL> mtls;
};

	}
}

#endif