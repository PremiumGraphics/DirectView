#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include "../Math/Volume.h"
#include "../Math/Line.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Brush.h"

namespace Crystal {
	namespace Graphics {

class DisplayList final
{
public:
	DisplayList() = default;

	~DisplayList() = default;

	void add(const DisplayList& rhs) {
		brushes.insert(brushes.end(), rhs.brushes.begin(), rhs.brushes.end());
		lines.insert(lines.end(), rhs.lines.begin(), rhs.lines.end());
		volumes.insert(volumes.end(), rhs.volumes.begin(), rhs.volumes.end());
		surfaces.insert(surfaces.end(), rhs.surfaces.begin(), rhs.surfaces.end());
	}

	void add(const Graphics::BlendBrush<float>& b) {
		brushes.push_back(b);
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
		brushes.clear();
		lines.clear();
		volumes.clear();
		surfaces.clear();
	}

	Brush3dVector<float> getBrushes() const { return brushes; }

	Math::Line3dVector<float> getLines() const { return lines; }

	Math::Volume3dSPtrList<float> getVolumes() const { return volumes; }

	Graphics::SurfaceSPtrList<float> getSurfaces() const { return surfaces; }

private:
	Brush3dVector<float> brushes;
	Math::Line3dVector<float> lines;
	Math::Volume3dSPtrList<float> volumes;
	Graphics::SurfaceSPtrList<float> surfaces;
};
	}
}

#endif