#ifndef __CRYSTAL_UI_VOLUME_COMMAND_H__
#define __CRYSTAL_UI_VOLUME_COMMAND_H__

namespace Crystal {
	namespace UI{


template<typename T>
class VolumeConfig {
public:
	VolumeConfig() {
		setDefault();
	}

	void setDefault() {
		resx = 20;
		resy = 20;
		resz = 20;
		threshold = 0.5;
		space = Math::Space3d<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(2, 2, 2));
	}

	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
	double threshold;
	Math::Space3d<T> space;
};


class VolumeCommand final
{
public:
	VolumeCommand() = default;

	~VolumeCommand() = default;

	void setupVolumes(const VolumeConfig<float>& vConfig)
	{
		Math::Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
		Math::Volume3d<float> v(vConfig.space, grid);
		preVolume = v;
		bakedVolume = v;
	}


	void clear() {
		preVolume.setValue(0);
		bakedVolume.setValue(0);
	}

	void bake() {
		bakedVolume = preVolume;
	}

	void add(const std::list<Math::Particle3d<float>>& particles, const float factor) {
		preVolume = bakedVolume;
		for (const auto& p : particles) {
			preVolume.add(p, factor);
		}
	}

	void add(const Math::Particle3d<float>& particle, const float factor) {
		preVolume = bakedVolume;
		preVolume.add(particle, factor);
	}

	Math::Volume3d<float> getPreVolume() const { return preVolume; }

	Math::Volume3d<float> getBakedVolume() const { return bakedVolume; }

private:
	Math::Volume3d<float> preVolume;
	Math::Volume3d<float> bakedVolume;

};

	}
}

#endif