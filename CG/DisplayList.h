#ifndef __CRYSTAL_UI_DISPLAY_LIST_H__
#define __CRYSTAL_UI_DISPLAY_LIST_H__

#include "../Math/Particle.h"
#include "../Math/Line.h"

namespace Crystal {
	namespace UI {

class DisplayList {
public:

	void add(const DisplayList& rhs) {
		particles.insert(particles.end(), rhs.particles.begin(), rhs.particles.end());
		lines.insert(lines.end(), rhs.lines.begin(), rhs.lines.end());
	}

	void add(const Math::ParticleSPtr<float>& p) {
		particles.push_back(p);
	}

	void add(const Math::Line3d<float>& l) {
		lines.push_back(l);
	}

	void clear(){
		particles.clear();
		lines.clear();
	}

private:
	Math::ParticleSPtrList<float> particles;
	Math::Line3dVector<float> lines;
};
	}
}

#endif