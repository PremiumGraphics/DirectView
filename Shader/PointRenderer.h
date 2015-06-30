#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "../Graphics/Buffer.h"
#include "../Graphics/Camera.h"
#include "ShaderObject.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class PointRenderer final : private UnCopyable
{
public:

	PointRenderer() = default;

	~PointRenderer() = default;

	void add(const Graphics::Surface<float>& surface, const int id, const int isSelected) {
		for (const auto& e : surface.getEdges()) {
			addPosition(e->getStartPosition(), e->getStartVertex()->getNormal(), id, isSelected);
		}
			//positions.add( surface.)
	}
	void clear() {
		positions.clear();
		normals.clear();
	}

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const bool isSelected);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint isSelected;
	};

	Location getLocations();

	void addPosition(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const int id, const int isSelected) {
		const auto& poss = position.toArray();
		positions.insert(positions.end(), poss.begin(), poss.end());
		const auto& norms = normal.toArray();
		normals.insert(normals.end(), norms.begin(), norms.end());
	}


	std::vector<float> positions;
	std::vector<float> normals;


	ShaderObject shader;
};

	}
}

#endif