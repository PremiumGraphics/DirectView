#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Shader {

class IDRenderer {
public:

	IDRenderer();

	~IDRenderer();

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

	void build();

	void add(const Math::Vector3d<float>& v, const unsigned int type, const unsigned int id) {
		const auto& cs = v.toArray();
		positions.insert(positions.end(), cs.begin(), cs.end());
		types.push_back(type);
		ids.push_back(id);
	}

	void clear() {
		positions.clear();
		types.clear();
		ids.clear();
	}

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint type;
		GLuint id;
	};

	Location getLocations();


	std::vector<float> positions;
	std::vector<int> types;
	std::vector<int> ids;


	Graphics::ShaderObject shader;
};

	}
}

#endif