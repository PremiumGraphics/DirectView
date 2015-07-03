#ifndef __CRYSTAL_SHADER_WIREFRAME_RENDERER_H__
#define __CRYSTAL_SHADER_WIREFRAME_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Math/Volume.h"
#include "../Math/Line.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class WireframeRenderer final : private UnCopyable
{
public:

	WireframeRenderer() = default;

	~WireframeRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const bool isSelected);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
		GLuint isSelected;
	};

	Location getLocations();

	ShaderObject shader;

public:
	void clear() {
		positions.clear();
	}

	void add(const Math::Volume3d<float>& volume) {
		const Math::Box<float> v(volume.getStart(), volume.getEnd());
		add(v);
	}

	void add(const Graphics::Surface<float>& surface) {
		for (const auto& e : surface.getEdges()) {
			add(e->getStartPosition());
			add(e->getEndPosition());
		}
		//positions.add( surface.)
	}

	void add(const Math::Line3d<float>& line) {
		add(line.getStart());
		add(line.getEnd());
	}

	void add(const Math::Vector3d<float>& position) {
		const auto& poss = position.toArray3();
		positions.insert(positions.end(), std::begin(poss), std::end(poss));
	}


private:
	std::vector<float> positions;

public:
	void add(const Math::Box<float>& box) {
		const auto minx = box.getMinX();
		const auto miny = box.getMinY();
		const auto minz = box.getMinZ();
		const auto maxx = box.getMaxX();
		const auto maxy = box.getMaxY();
		const auto maxz = box.getMaxZ();

		const Math::Vector3dVector<float> vs = {
			Math::Vector3d<float>(minx, miny, minz),
			Math::Vector3d<float>(maxx, miny, minz),
			Math::Vector3d<float>(maxx, maxy, minz),
			Math::Vector3d<float>(minx, maxy, minz),
			Math::Vector3d<float>(minx, miny, maxz),
			Math::Vector3d<float>(maxx, miny, maxz),
			Math::Vector3d<float>(maxx, maxy, maxz),
			Math::Vector3d<float>(minx, maxy, maxz)
		};

		const Math::Line3dVector<float> lines{
			Math::Line3d<float>(vs[0], vs[1]),
			Math::Line3d<float>(vs[1], vs[2]),
			Math::Line3d<float>(vs[2], vs[3]),
			Math::Line3d<float>(vs[3], vs[0]),
			Math::Line3d<float>(vs[4], vs[5]),
			Math::Line3d<float>(vs[5], vs[6]),
			Math::Line3d<float>(vs[6], vs[7]),
			Math::Line3d<float>(vs[7], vs[4]),
			Math::Line3d<float>(vs[0], vs[4]),
			Math::Line3d<float>(vs[1], vs[5]),
			Math::Line3d<float>(vs[2], vs[6]),
			Math::Line3d<float>(vs[3], vs[7])
		};

		for (const auto& l : lines) {
			add(l);
		}

	}

};

	}
}

#endif