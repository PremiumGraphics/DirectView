#ifndef __CRYSTAL_UI_DISPLAY_LIST_H__
#define __CRYSTAL_UI_DISPLAY_LIST_H__

#include "../Math/Particle.h"
#include "../Math/Line.h"

namespace Crystal {
	namespace UI {

class DisplayList {
public:

	DisplayList() = default;

	~DisplayList() = default;

	void add(const DisplayList& rhs) {
		particles.insert(particles.end(), rhs.particles.begin(), rhs.particles.end());
		lines.insert(lines.end(), rhs.lines.begin(), rhs.lines.end());
	}

	void add(const Math::Particle3d<float>& p) {
		particles.push_back(p);
	}

	void add(const Math::Line3d<float>& l) {
		lines.push_back(l);
	}

	void clear(){
		particles.clear();
		lines.clear();
	}

	std::list< Math::Particle3d<float> > getParticles() const { return particles; }

	Math::Line3dVector<float> getLines() const { return lines; }

private:
	std::list< Math::Particle3d<float> > particles;
	Math::Line3dVector<float> lines;
};
	}
}

#endif