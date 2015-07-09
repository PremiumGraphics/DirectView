#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include "../Math/Particle.h"
#include "../Math/Volume.h"
#include "../Math/Line.h"
#include "../Graphics/Surface.h"

namespace Crystal {
	namespace Graphics {

class DisplayList final
{
public:
	DisplayList() = default;

	~DisplayList() = default;

	void add(const DisplayList& rhs) {
		particles.insert(particles.end(), rhs.particles.begin(), rhs.particles.end());
		lines.insert(lines.end(), rhs.lines.begin(), rhs.lines.end());
		volumes.insert(volumes.end(), rhs.volumes.begin(), rhs.volumes.end());
		surfaces.insert(surfaces.end(), rhs.surfaces.begin(), rhs.surfaces.end());
	}

	void add(const Math::Particle3d<float>& p) {
		particles.push_back(p);
	}

	void add(const Math::Line3d<float>& l) {
		lines.push_back(l);
	}

	void add(const Math::Volume3dSPtr<float>& v) {
		volumes.push_back(v);
	}

	void add(const Graphics::SurfaceSPtr<float>& s) {
		surfaces.push_back(s);
	}

	void clear(){
		particles.clear();
		lines.clear();
		volumes.clear();
		surfaces.clear();
	}

	std::list< Math::Particle3d<float> > getParticles() const { return particles; }

	Math::Line3dVector<float> getLines() const { return lines; }

	Math::Volume3dSPtrList<float> getVolumes() const { return volumes; }

	Graphics::SurfaceSPtrList<float> getSurfaces() const { return surfaces; }

private:
	std::list< Math::Particle3d<float> > particles;
	Math::Line3dVector<float> lines;
	Math::Volume3dSPtrList<float> volumes;
	Graphics::SurfaceSPtrList<float> surfaces;
};
	}
}

#endif